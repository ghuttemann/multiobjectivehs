/*  This file is part of mohs.

    Copyright (C) 2011 GermÃ¡n HÃ¼ttemann <ghuttemann@gmail.com>
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

#ifndef HARMONYSEARCH_H
#define	HARMONYSEARCH_H

#include "HS/Algorithm.h"
#include "HS_Structures/Memory/Memory.h"
#include "HS_Operators/PitchAdjustment/PitchAdjustment.h"
#include "HS_Operators/MemoryConsideration/MemoryConsideration.h"
#include "HS_Operators/MemoryUpdate/MemoryUpdate.h"
#include "HS_Operators/ParetoRanking/ParetoRanking.h"
#include "HS_Structures/Memory/MemoryBuilder/MemoryBuilder.h"
#include "HS_Operators/MemoryInit/MemoryInit.h"

#include <list>
using namespace std;

class HarmonySearch : public Algorithm {
protected:
    /* Algorithm set-up */
    HS_Params *hsParams;
    
    /* Memory builder algorithm */
    MemoryBuilder *memoryBuilder;

    /* Memory initialization algorithm */
    MemoryInit *memoryInit;

    /* Memory update algorithm */
    MemoryUpdate *memoryUpdate;

    /* Memory consideration algoritm */
    MemoryConsideration *memoryConsideration;
    
    /* Pitch Adjustment algorithm */
    PitchAdjustment *pitchAdjustment;

    /* Pareto ranking computation algorithm */
    ParetoRanking *paretoRanking;

    /* Algorithm Memory */
    Memory *mainMemory;

    /* Builds a new solution performing improvisation  */
    Solution *buildSolution(Random *random);

    /* Prints the results */
    void printResults(Timer *totalTimer, Timer *globalTimer, int iterations,
        int maxPareto, metrics_t *metrics);

    /* Pareto set initialization */
    void initParetoSet();

    /*
     * Copies all memory solutions to Pareto set,
     * removing non-dominated ones.
     */
    void copyMemoryToParetoSet();

public:
    /** Constructor. */
    HarmonySearch(Problem *problem, HS_Params *hsParams, MemoryBuilder *memoryBuilder,
            MemoryInit *memoryInit, MemoryConsideration *memoryConsideration,
            PitchAdjustment *pitchAdjustment, MemoryUpdate *memoryUpdate,
            ParetoRanking *paretoRanking, bool calculateAndPrintMetrics, bool doSampling);

    /** Destructor. */
    virtual ~HarmonySearch() = 0;

    /** Algorithm execution. */
    virtual void run() = 0;

    /** Get the algorithm name. */
    virtual const char *getName() = 0;
};

#endif	/* HARMONYSEARCH_H */
