/*  This file is part of mohs.

    Copyright (C) 2011 Germán Hüttemann <ghuttemann@gmail.com>
    Copyright (C) 2011 Juan Ricart <juangabriel.ricart@gmail.com>

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

#include "HS/HarmonySearch.h"
#include <cstdlib>
#include <cstdio>

HarmonySearch::HarmonySearch(Problem *problem, HS_Params *hsParams,
	MemoryBuilder *memoryBuilder, MemoryInit *memoryInit,
        MemoryConsideration *memoryConsideration,
        PitchAdjustment *pitchAdjustment, MemoryUpdate *memoryUpdate,
        ParetoRanking *paretoRanking,
        bool calculateAndPrintMetrics, bool doSampling) : Algorithm(problem,
        hsParams, calculateAndPrintMetrics, doSampling) {
    
    this->memoryBuilder = memoryBuilder;
    this->memoryInit = memoryInit;
    this->memoryConsideration = memoryConsideration;
    this->pitchAdjustment = pitchAdjustment;
    this->memoryUpdate = memoryUpdate;
    this->paretoRanking = paretoRanking;
    
    mainMemory = memoryBuilder->createMemory(hsParams->getHMS(), problem);
}

HarmonySearch::~HarmonySearch() {
    delete mainMemory;
}

Solution *HarmonySearch::buildSolution(Random* random) {
    Solution *xNew = new Solution(problem->getSize(), problem->getObjectives());

    for (int i=0; i < xNew->getSize(); i++) {
        Variable *value = NULL;

        double rand = random->boundedRandom(0, 1);
        if (rand < hsParams->getHMCR()) {
            /* Memory Consideration */
            value = memoryConsideration->selectVariable(problem, mainMemory, i, random);

            /* Pitch Adjustment */
            rand = random->boundedRandom(0, 1);
            if (rand < hsParams->getPAR())
                value = pitchAdjustment->adjust(problem, i, value, random);
        }
        else {
            /* Random Selection */
            value = randomSelection(i, random);
        }

        /* Save new calculated variable */
        xNew->setVariable(i, value);
    }

    return xNew;
}

void HarmonySearch::printResults(Timer* totalTimer, Timer* globalTimer, 
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

    /* Prints HS set-up (file 1) */
    fprintf(output1, "HMCR ================= %f\n", hsParams->getHMCR());
    fprintf(output1, "PAR ================== %f\n", hsParams->getPAR());
    fprintf(output1, "SETFW ================ %d\n", hsParams->getSetFW());
    fprintf(output1, "REALFW =============== %f\n", hsParams->getRealFW());
    fprintf(output1, "BINFW ================ %f\n", hsParams->getBinFW());
    fprintf(output1, "HMS ================== %d\n", hsParams->getHMS());
    fprintf(output1, "TMPHMS =============== %d\n", hsParams->getTmpHMS());
    fprintf(output1, "STOP ================= %d\n", hsParams->getStoppingCriteria());
    fprintf(output1, "MAXITERATION ========= %d\n", hsParams->getMaxIteration());
    fprintf(output1, "TIME ================= %lld\n", hsParams->getMiliseconds());
    fprintf(output1, "CYCLES =============== %d\n", hsParams->getCycles());
    fprintf(output1, "SAMPLING ============= %d\n",  hsParams->getSamplingCriteria());
    fprintf(output1, "INTERVAL ============= %lld\n", hsParams->getInterval());
    fprintf(output1, "PSMAXSIZE ============ %d\n", hsParams->getParetoSetMaxSize());
    fprintf(output1, "PSMAXGROWTH ========== %d\n", hsParams->getParetoSetMaxGrowth());
    fprintf(output1, "EPSILONM1 ============ %f\n", hsParams->getEpsilonM1());
    fprintf(output1, "DEBUG ================ %d\n", hsParams->getDebug());
    fprintf(output1, "FRONTMINSIZE ========= %d\n", hsParams->getFrontMinSize());
    fprintf(output1, "TRUNCATEPERCENTAGE === %f\n", hsParams->getTruncatePercentage());
    fprintf(output1, "\n");
    fprintf(output1, "MEMORY_INIT ========== %s\n", memoryInit->getName());
    fprintf(output1, "MEMORY_CONS ========== %s\n", memoryConsideration->getName());
    fprintf(output1, "MEMORY_UPDATE ======== %s\n", memoryUpdate->getName());
    fprintf(output1, "MEMORY BUILDER ======= %s\n", memoryBuilder->getName());
    fprintf(output1, "PITCH_ADJUST ========= %s\n", pitchAdjustment->getName());
    fprintf(output1, "PARETO_RANK ========== %s\n", paretoRanking->getName());
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

    /* Prints memory (file 1) */
    fprintf(output1, "MEMORY\n");
    fprintf(output1, "Obj_Func1\tObj_Func2\tVariables\n");
    mainMemory->print(output1, true, true);
    fclose(output1);

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

void HarmonySearch::initParetoSet() {
    /*
     * Copy created solutions and save them in
     * Pareto set.
     */
    for (int i=0; i < mainMemory->getSize(); i++) {
        Solution *sol = mainMemory->getSolution(i);
        Solution *tmp = sol->clone(problem->getVariableBuilder());
        paretoSet->add(tmp);
    }

    /* Remove dominated solutions from Pareto set */
    paretoSet->removeDominated();
}

void HarmonySearch::copyMemoryToParetoSet() {
    for (int i=0; i < mainMemory->getSize(); i++) {
        Solution *sol = mainMemory->getSolution(i);
        if (sol->getRanking() == 1)
            paretoSet->add(sol->clone(problem->getVariableBuilder()));
    }
}
