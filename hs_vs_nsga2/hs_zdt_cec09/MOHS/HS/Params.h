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

#ifndef PARAMS_H
#define	PARAMS_H

class Params {
private:
    /* Stopping Criteria */
    int stoppingCriteria;

    /* Sampling Criteria */
    int samplingCriteria;

    /* Maximum Iteration */
    int maxIteration;

    /* Milliseconds of execution */
    long long miliseconds;

    /* Algorithm sampling interval */
    long long samplingInterval;

    /* Algorithm number of cycles */
    int cycles;

    /* Debug flag */
    int debug;

    /* Metric M1 convergence epsilon */
    double epsilonM1;

public:
    /* Constructors */
    Params(const char *path);

    /* Destructor */
    ~Params();
    
    /* Getters */
    int getStoppingCriteria() const;
    int getSamplingCriteria() const;
    int getMaxIteration() const;
    long long getMiliseconds() const;
    long long getInterval() const;
    int getCycles() const;
    bool getDebug() const;
    double getEpsilonM1() const;
};

#endif	/* PARAMS_H */
