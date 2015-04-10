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

#include "Problem/DTLZ/DTLZ1.h"
#include <cmath>

DTLZ1::DTLZ1(int m, const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : DTLZ(objectives, path, hsParams, varBuilder) {
    
}

DTLZ1::~DTLZ1() {
    
}

void DTLZ1::calculate_f(const Solution *sol, double g, double *f) {
    for (int i=0; i < getM(); i++) {
        f[i] = 0.5 * (1 + g);
        
        for (int j=0; j < getM() - i - 1; j++) {
            double xj = ((RealVariable *) sol->getVariable(j))->getValue();
            f[i] *= xj;
        }
        
        if (i != 0) {
            int j = getM() - i - 1;
            double xj = ((RealVariable *) sol->getVariable(j))->getValue();
            f[i] *= 1 - xj;
        }
    }
}

double DTLZ1::calculate_g(const Solution *sol) {
    double g = 0;
    
    for (int i=getM()-1; i < getN(); i++) {
        double xi = ((RealVariable *) sol->getVariable(i))->getValue();
        double h = (xi - 0.5);
        g += h*h - cos(20*PI*h);
    }
    
    g = 100 * (getK() + g);
    return g;
}

double DTLZ1::paretoOrdinate(double x) {
    
}

double DTLZ1::getMaxDistance() const {
    
}

const char *DTLZ1::getName() {
    return "DTLZ1";
}
