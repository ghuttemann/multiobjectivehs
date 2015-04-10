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

#include "HS/Algorithm.h"
#include <cstdlib>
#include <cstdio>

Algorithm::Algorithm(Problem *problem, Params *params,
	bool calculateAndPrintMetrics, bool doSampling) {
    
    this->problem = problem;
    this->hsParams = params;
    this->calculateAndPrintMetrics = calculateAndPrintMetrics;
    this->doSampling = doSampling;

    paretoSet = new ParetoSet();
    if (calculateAndPrintMetrics)
        yTrue = problem->optimalParetoFront();
    else
        yTrue = NULL;
}

Algorithm::~Algorithm() {
    delete paretoSet;
    delete yTrue;
}

bool Algorithm::stoppingCondition(int cycle, int iterations, Timer *timer) {
    if (hsParams->getStoppingCriteria() == 0 && iterations < hsParams->getMaxIteration() * cycle)
        return false;
    else if (hsParams->getStoppingCriteria() == 1 && !timer->hasElapsed(hsParams->getMiliseconds()))
        return false;

    return true;
}

bool Algorithm::intervalCondition(int iterations, Timer* timer) {
    if (hsParams->getSamplingCriteria() == 1 && timer->hasElapsed(hsParams->getInterval()))
        return true;
    else if (hsParams->getSamplingCriteria() == 0 && iterations % hsParams->getInterval() == 0)
        return true;

    return false;
}

Variable *Algorithm::randomSelection(int variable, Random *random) {
    /* Get lower bound of variable range */
    Variable *min = problem->getMinimum(variable);

    /* Get upper bound of variable range */
    Variable *max = problem->getMaximum(variable);

    /* Creates new variable between range */
    Variable *result = problem->getVariableBuilder()->createVariable(min, max, random);
    return result;
}

void Algorithm::sampling(NonDominatedSet *points, int iterations,
        Timer *globalTimer, FILE *samplingOutput) {

    if (doSampling) {
        globalTimer->pause();
        printSampling(points, iterations, globalTimer, samplingOutput);
        globalTimer->resume();
    }
}

void Algorithm::printSampling(NonDominatedSet *points, int iterations,
        Timer *globalTimer, FILE *samplingOutput) {

    /* Prints Pareto front */
    fprintf(samplingOutput, "# Solutions: %d\n", points->getNonDominatedSize());
    fprintf(samplingOutput, "# Timestamp: %lld\n", globalTimer->getElapsed());
    fprintf(samplingOutput, "# Iterations: %d\n", iterations);
    points->printNonDominated(samplingOutput, false, false);
    fflush(samplingOutput);
}

void Algorithm::getDate(char *buffer) {
    char mon[3], day[3], hour[3], min[3], sec[3];
    time_t t;
    struct tm *d;

    time(&t);
    d = localtime(&t);

    if (d->tm_mon + 1 < 10)
        sprintf(mon, "0%d", d->tm_mon + 1);
    else
        sprintf(mon, "%d", d->tm_mon + 1);

    if (d->tm_mday < 10)
        sprintf(day, "0%d", d->tm_mday);
    else
        sprintf(day, "%d", d->tm_mday);

    if (d->tm_hour < 10)
        sprintf(hour, "0%d", d->tm_hour);
    else
        sprintf(hour, "%d", d->tm_hour);

    if (d->tm_min < 10)
        sprintf(min, "0%d", d->tm_min);
    else
        sprintf(min, "%d", d->tm_min);

    if (d->tm_sec < 10)
        sprintf(sec, "0%d", d->tm_sec);
    else
        sprintf(sec, "%d", d->tm_sec);

    sprintf(buffer, "%d.%s.%s.%s.%s.%s", d->tm_year + 1900, mon, day, hour, min, sec);
}

void Algorithm::calculateMetrics(metrics_t *metrics, ParetoSet *paretoSet) {
    metrics->absM1 = paretoSet->metricM1(yTrue);
    metrics->absM2 = paretoSet->metricM2();
    metrics->absM3 = paretoSet->metricM3();

    metrics->normM1 = metrics->absM1;
    metrics->normM2 = metrics->absM2 / paretoSet->getSize();
    metrics->normM3 = metrics->absM3 / yTrue->metricM3();

    metrics->error = paretoSet->metricError(yTrue);
    metrics->igd = yTrue->metricM1(paretoSet);
    metrics->solutions = paretoSet->getSize();
}
