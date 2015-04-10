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

#include "HS/HS_Params.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>

HS_Params::HS_Params(const char *path) : Params(path) {
    FILE *file;
    char buffer[30];
    const int PARAMS = 11;
    int count = 0;

    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file '%s' in read mode\n", path);
        exit(EXIT_FAILURE);
    }

    while (!feof(file)) {
        buffer[0] = '\0';
        fscanf(file, "%s", buffer);
        
        if (strcasecmp(buffer, "HMCR") == 0) {
            fscanf(file, "%lf", &hmcr);
            ++count;
        }
        else if (strcasecmp(buffer, "PAR") == 0) {
            fscanf(file, "%lf", &par);
            ++count;
        }
        else if (strcasecmp(buffer, "SETFW") == 0) {
            fscanf(file, "%d", &setFW);
            ++count;
        }
        else if (strcasecmp(buffer, "REALFW") == 0) {
            fscanf(file, "%lf", &realFW);
            ++count;
        }
        else if (strcasecmp(buffer, "BINFW") == 0) {
            fscanf(file, "%lf", &binFW);
            ++count;
        }
        else if (strcasecmp(buffer, "HMS") == 0) {
            fscanf(file, "%d", &hms);
            ++count;
        }
        else if (strcasecmp(buffer, "TMPHMS") == 0) {
            fscanf(file, "%d", &tmpHms);
            ++count;
        }
        else if (strcasecmp(buffer, "PSMAXSIZE") == 0) {
            fscanf(file, "%d", &psMaxSize);
            ++count;
        }
        else if (strcasecmp(buffer, "PSMAXGROWTH") == 0) {
            fscanf(file, "%d", &psMaxGrowth);
            ++count;
        }
        else if (strcasecmp(buffer, "FRONTMINSIZE") == 0) {
            fscanf(file, "%d", &frontMinSize);
            ++count;
        }
        else if (strcasecmp(buffer, "TRUNCATEPERCENTAGE") == 0) {
            fscanf(file, "%lf", &truncatePercentage);
            ++count;
        }
    }

    /* Parameters validation */
    assert(count == PARAMS);
    assert(hmcr >= 0);
    assert(par >= 0);
    assert(setFW == 0 || setFW == 1);
    assert(realFW > 0 && realFW < 100);
    assert(binFW > 0 && binFW < 100);
    assert(hms > 0);
    assert(tmpHms > 0);
    assert(psMaxSize > 0);
    assert(psMaxGrowth > 0 && psMaxGrowth > psMaxSize);
    assert(frontMinSize > 0);
    assert(truncatePercentage >= 0.0 && truncatePercentage <= 100.0);

    fclose(file);
}

HS_Params::~HS_Params() {

}

int HS_Params::getHMS() const {
    return hms;
}

int HS_Params::getTmpHMS() const {
    return tmpHms;
}

double HS_Params::getPAR() const {
    return par;
}

double HS_Params::getHMCR() const {
    return hmcr;
}

int HS_Params::getSetFW() const {
    return setFW;
}

double HS_Params::getRealFW() const {
    return realFW;
}

double HS_Params::getBinFW() const {
    return binFW;
}

int HS_Params::getParetoSetMaxSize() const {
    return psMaxSize;
}

int HS_Params::getParetoSetMaxGrowth() const {
    return psMaxGrowth;
}

int HS_Params::getFrontMinSize() const {
    return frontMinSize;
}

double HS_Params::getTruncatePercentage() const {
    return truncatePercentage;
}
