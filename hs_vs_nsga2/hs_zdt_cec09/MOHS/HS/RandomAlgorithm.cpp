/*  This file is part of mohs.

    Copyright (C) 2013 Germán Hüttemann <ghuttemann@gmail.com>
    Copyright (C) 2013 Juan Ricart <juangabriel.ricart@gmail.com>

    mohs is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    mohs is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with mohs.  If not, see <http://www.gnu.org/licenses/>. */

#include "HS/RandomAlgorithm.h"
#include <cstdlib>
#include <cstdio>

RandomAlgorithm::RandomAlgorithm(Problem *problem, Params *params,
        bool calculateAndPrintMetrics, bool doSampling) : Algorithm(problem, 
        params, calculateAndPrintMetrics, doSampling) {
    
    this->problem = problem;
    this->params = params;
    this->calculateAndPrintMetrics = calculateAndPrintMetrics;
    this->doSampling = doSampling;

    paretoSet = new ParetoSet();
    if (calculateAndPrintMetrics)
        yTrue = problem->optimalParetoFront();
    else
        yTrue = NULL;
}

RandomAlgorithm::~RandomAlgorithm() {
    delete paretoSet;
    delete yTrue;
}

void RandomAlgorithm::run() {
    /* Random number generator */
    Random *random = new Random();

    /* Program total timer */
    Timer *totalTimer = new Timer();

    /* Algorithm global timer */
    Timer *globalTimer = new Timer();

    /* Iterations timer */
    Timer *iterTimer = new Timer();

    /* File where samples are written */
    FILE *samplingOutput;

    /* Gets date/time of execution */
    getDate(this->date);

    if (doSampling) {
        char buffer[50];

        sprintf(buffer, "sampling%s.txt", date);
        if ((samplingOutput = fopen(buffer, "w")) == NULL) {
            fprintf(stderr, "Error opening file '%s' in write mode", buffer);
            exit(EXIT_FAILURE);
        }
    }

    /* Print algorithm and problem */
    printf("%s(%s)\n", this->getName(), problem->getName());

    if (params->getDebug()) {
        paretoSet->print(stdout, true, true);
        fprintf(stdout, "--------------\n");
    }

    /* Iterations counter */
    int cycles = 0;
    int iterations = 0;

    /* Timers */
    totalTimer->start();
    globalTimer->start();
    iterTimer->start();

    /* Main loop */
    printf("Improvisation begins...\n");
    while (cycles < params->getCycles()) {
        while (!stoppingCondition(cycles + 1, iterations, iterTimer)) {

            /* Build new solution */
            Solution *xNew = buildSolution(random);

            /* Evaluate solution */
            problem->evaluate(xNew);

            /* Update Pareto set */
            Solution *p = xNew->clone(problem->getVariableBuilder());
            paretoSet->nonDominatedAdd(p);

            if (params->getDebug()) {
                xNew->print(stdout, true);
                fprintf(stdout, "--------------\n");
            }
            delete xNew;
            ++iterations;
        }

        /* Sampling */
        sampling(paretoSet, iterations, globalTimer, samplingOutput);

        /* Increment cycles */
        ++cycles;

        /* Sampling timer reset */
        iterTimer->start();
    }

    /* Get finalization time */
    globalTimer->split();
    printf("Improvisation finishes...\n");

    if (doSampling) {
        fclose(samplingOutput);
    }

    /* Calculate metrics */
    metrics_t metrics;
    if (calculateAndPrintMetrics) {
        printf("Calculating metrics...\n");
        calculateMetrics(&metrics, paretoSet);
    }

    /* Print results */
    printf("Printing results...\n");
    printResults(totalTimer, globalTimer, iterations, paretoSet->getSize(), &metrics);

    delete random;
    delete totalTimer;
    delete globalTimer;
    delete iterTimer;
}

Solution *RandomAlgorithm::buildSolution(Random* random) {
    Solution *xNew = new Solution(problem->getSize(), problem->getObjectives());

    for (int i=0; i < xNew->getSize(); i++) {
        /* Random Selection */
        Variable *value = randomSelection(i, random);

        /* Save new calculated variable */
        xNew->setVariable(i, value);
    }

    return xNew;
}

void RandomAlgorithm::printResults(Timer* totalTimer, Timer* globalTimer, 
        int iterations, int maxPareto, metrics_t* metrics) {

    /* Output files buffers */
    char buffer1[50], buffer2[50], buffer3[50];
    FILE *output1, *output2, *output3;

    sprintf(buffer1, "output%s.txt", date);
    sprintf(buffer2, "pareto%s.txt", date);
    sprintf(buffer3, "metric%s.txt", date);

    /* Opens output file 1 */
    if ((output1 = fopen(buffer1, "w")) == NULL) {
        fprintf(stderr, "Error opening file '%s' in write mode", buffer1);
        exit(EXIT_FAILURE);
    }

    /* Opens output file 2 */
    if ((output2 = fopen(buffer2, "w")) == NULL) {
        fprintf(stderr, "Error opening file '%s' in write mode", buffer2);
        exit(EXIT_FAILURE);
    }

    /* Opens output file 3 */
    if (calculateAndPrintMetrics) {
        if ((output3 = fopen(buffer3, "w")) == NULL) {
            fprintf(stderr, "Error opening file '%s' in write mode", buffer3);
            exit(EXIT_FAILURE);
        }
    }

    /* Prints solved problem (file 1) */
    fprintf(output1, "ALGORITHM ====== %s\n", this->getName());
    fprintf(output1, "PROBLEM ======== %s(%d)\n", problem->getName(), problem->getSize());
    fprintf(output1, "\n");

    /* Prints RandomAlgorithm set-up (file 1) */
    fprintf(output1, "STOP ================= %d\n", params->getStoppingCriteria());
    fprintf(output1, "MAXITERATION ========= %d\n", params->getMaxIteration());
    fprintf(output1, "TIME ================= %lld\n", params->getMiliseconds());
    fprintf(output1, "CYCLES =============== %d\n", params->getCycles());
    fprintf(output1, "SAMPLING ============= %d\n",  params->getSamplingCriteria());
    fprintf(output1, "INTERVAL ============= %lld\n", params->getInterval());
    fprintf(output1, "EPSILONM1 ============ %f\n", params->getEpsilonM1());
    fprintf(output1, "DEBUG ================ %d\n", params->getDebug());
    fprintf(output1, "\n");
    fflush(output1);

    /* Prints status data (file 1) */
    fprintf(output1, "TiempoTotal TiempoGlobal Iteracion Cant Max\n");
    fprintf(output1, "%lld %lld %d %d %d\n", totalTimer->getElapsed(), globalTimer->lastSplit(), iterations,
                paretoSet->getSize(), maxPareto);
    fprintf(output1, "\n");
    fflush(output1);

    /* Prints Pareto solutions (file 1) */
    fprintf(output1, "PARETO FRONT/SET\n");
    fprintf(output1, "Obj_Func1\tObj_Func2\tVariables\n");
    paretoSet->print(output1, true, true);
    fprintf(output1, "\n");

    /* Prints Pareto front (file 2) */
    fprintf(output2, "# Problem: %s(%d)\n", problem->getName(), problem->getSize());
    fprintf(output2, "# Solutions: %d\n", paretoSet->getSize());
    paretoSet->print(output2, false, false);
    fclose(output2);

    /* Prints metrics (file 3) */
    if (calculateAndPrintMetrics) {
        fprintf(output3, "%f\t", metrics->absM1);
        fprintf(output3, "%f\t", metrics->normM1);

        fprintf(output3, "%f\t", metrics->absM2);
        fprintf(output3, "%f\t", metrics->normM2);

        fprintf(output3, "%f\t", metrics->absM3);
        fprintf(output3, "%f\t", metrics->normM3);

        fprintf(output3, "%f\t", metrics->error);
        fprintf(output3, "%f\t", metrics->igd);
        fprintf(output3, "%d\n", metrics->solutions);
        fclose(output3);
    }
}

const char *RandomAlgorithm::getName() {
    return "RandomAlgorithm";
}
