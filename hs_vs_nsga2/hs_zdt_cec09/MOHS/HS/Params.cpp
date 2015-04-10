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

#include "HS/Params.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>

Params::Params(const char *path) {
    FILE *file;
    char buffer[30];
    const int PARAMS = 8;
    int count = 0;

    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file '%s' in read mode\n", path);
        exit(EXIT_FAILURE);
    }

    while (!feof(file)) {
        buffer[0] = '\0';
        fscanf(file, "%s", buffer);
        
        if (strcasecmp(buffer, "STOP") == 0) {
            fscanf(file, "%d", &stoppingCriteria);
            ++count;
        }
        else if (strcasecmp(buffer, "SAMPLING") == 0) {
            fscanf(file, "%d", &samplingCriteria);
            ++count;
        }
        else if (strcasecmp(buffer, "MAXITERATION") == 0) {
            fscanf(file, "%d", &maxIteration);
            ++count;
        }
        else if (strcasecmp(buffer, "TIME") == 0) {
            fscanf(file, "%lld", &miliseconds);
            ++count;
        }
        else if (strcasecmp(buffer, "CYCLES") == 0) {
            fscanf(file, "%d", &cycles);
            ++count;
        }
        else if (strcasecmp(buffer, "INTERVAL") == 0) {
            fscanf(file, "%lld", &samplingInterval);
            ++count;
        }
        else if (strcasecmp(buffer, "DEBUG") == 0) {
            fscanf(file, "%d", &debug);
            ++count;
        }
        else if (strcasecmp(buffer, "EPSILONM1") == 0) {
            fscanf(file, "%lf", &epsilonM1);
            ++count;
        }
    }

    /* Parameters validation */
    assert(count == PARAMS);
    assert(stoppingCriteria == 0 || stoppingCriteria == 1);
    assert(samplingCriteria == 0 || samplingCriteria == 1);
    assert(maxIteration > 0);
    assert(miliseconds > 0);
    assert(samplingInterval > 0);
    assert(cycles > 0);
    assert(debug == 0 || debug == 1);
    assert(epsilonM1 > 0);

    fclose(file);
}

Params::~Params() {

}

int Params::getStoppingCriteria() const {
    return stoppingCriteria;
}

int Params::getSamplingCriteria() const {
    return samplingCriteria;
}

int Params::getMaxIteration() const {
    return maxIteration;
}

long long Params::getMiliseconds() const {
    return miliseconds;
}

long long Params::getInterval() const {
    return samplingInterval;
}

int Params::getCycles() const {
    return cycles;
}

bool Params::getDebug() const {
    if (debug == 0)
        return false;

    return true;
}

double Params::getEpsilonM1() const {
    return epsilonM1;
}
