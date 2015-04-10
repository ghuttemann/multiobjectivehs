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

#ifndef ALGORITHM_H
#define	ALGORITHM_H

#include "Problem/Problem.h"
#include "HS/HS_Params.h"
#include "HS_Structures/Solution.h"
#include "Utils/Random.h"
#include "Utils/Timer.h"
#include "HS_Structures/Pareto/ParetoSet.h"
#include "HS_Structures/NonDominatedSet.h"

#include <list>
using namespace std;

class Algorithm {
protected:
    /* Problem to be solved */
    Problem *problem;

    /* Algorithm set-up */
    Params *hsParams;

    /* Algorithm Pareto set */
    ParetoSet *paretoSet;

    /* Problem optimal Front */
    ParetoSet *yTrue;

    /* Metrics computation set-up */
    bool calculateAndPrintMetrics;

    /* Sampling performing set-up */
    bool doSampling;

    /* Date/time of execution */
    char date[20];

    /* Builds a new solution performing improvisation  */
    virtual Solution *buildSolution(Random *random) = 0;

    /* Checks stopping criteria */
    bool stoppingCondition(int cycle, int iterations, Timer *timer);

    /* Checks interval condition */
    bool intervalCondition(int iterations, Timer *timer);

    /* Random selection */
    Variable *randomSelection(int variable, Random *random);

    /* 
     * Get an alphanumeric representation of current
     * date, in YYYY.MM.DD.HH24.MI.SS format.
     * The buffer passed as parameter must have at
     * least a size of 20 characters.
     */
    void getDate(char *buffer);

    /* Datatype for metrics */
    typedef struct {
        double absM1;   // Distance between calculated and optimal Pareto fronts
        double absM2;   // Distribution of calculated Pareto front
        double absM3;   // Extension of calculated Pareto front
        double normM1;  // Normalized M1
        double normM2;  // Normalized M2
        double normM3;  // Normalized M3
        double error;   // Percentage of solutions of calculated front that are not in optimal front
        double igd;     // Inverted Generational Distance (inverted M1)
        int solutions;  // Number of solutions of calculated Pareto front
    } metrics_t;

    void calculateMetrics(metrics_t *metrics, ParetoSet *yTrue);

    /* Sampling */
    void sampling(NonDominatedSet *points, int iterations,
        Timer *globalTimer, FILE *samplingOutput);

    /* Sampling print */
    void printSampling(NonDominatedSet *points, int iterations,
        Timer *globalTimer, FILE *samplingOutput);

    /* Prints the results */
    virtual void printResults(Timer *totalTimer, Timer *globalTimer, int iterations,
        int maxPareto, metrics_t *metrics) = 0;

public:
    /** Constructor. */
    Algorithm(Problem *problem, Params *params, 
            bool calculateAndPrintMetrics, bool doSampling);

    /** Destructor. */
    virtual ~Algorithm() = 0;

    /** Algorithm execution. */
    virtual void run() = 0;

    /** Get the algorithm name. */
    virtual const char *getName() = 0;
};

#endif	/* ALGORITHM_H */
