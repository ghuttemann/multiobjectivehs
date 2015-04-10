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

#ifndef RANDOMALGORITHM_H
#define	RANDOMALGORITHM_H

#include "HS/Params.h"
#include "HS/Algorithm.h"

class RandomAlgorithm : public Algorithm {
private:
    /* Algorithm set-up */
    Params *params;

    /* Builds a new solution performing random selection  */
    Solution *buildSolution(Random *random);

    /* Prints the results */
    void printResults(Timer *totalTimer, Timer *globalTimer, int iterations,
        int maxPareto, metrics_t *metrics);

public:
    /** Constructor. */
    RandomAlgorithm(Problem *problem, Params *params,
		    bool calculateAndPrintMetrics, bool doSampling);

    /** Destructor. */
    ~RandomAlgorithm();

    /** Algorithm running. */
    void run();

    /** Returns the algorithm name. */
    const char *getName();
};

#endif	/* RANDOMALGORITHM_H */
