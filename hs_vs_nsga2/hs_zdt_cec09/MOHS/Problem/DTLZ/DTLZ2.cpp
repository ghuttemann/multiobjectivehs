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

#include "Problem/DTLZ/DTLZ2.h"
#include <cmath>

DTLZ2::DTLZ2(int m, const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : DTLZ(objectives, path, hsParams, varBuilder) {
    
}

DTLZ2::~DTLZ2() {
    
}

void DTLZ2::calculate_f(const Solution *sol, double g, double *f) {
    for (int i=0; i < getM(); i++) {
        f[i] = 0.5 * (1 + g);
        
        for (int j=0; j < getM() - i - 1; j++) {
            double xj = ((RealVariable *) sol->getVariable(j))->getValue();
            f[i] *= cos(xj * PI * 0.5);
        }
        
        if (i != 0) {
            int j = getM() - i - 1;
            double xj = ((RealVariable *) sol->getVariable(j))->getValue();
            f[i] *= sin(xj * PI * 0.5);
        }
    }
}

double DTLZ2::calculate_g(const Solution *sol) {
    double g = 0;
    
    for (int i = getM() - 1; i < getN(); i++) {
        double xi = ((RealVariable *) sol->getVariable(i))->getValue();
        double h = (xi - 0.5);
        g += h*h;
    }
    
    return g;
}

double DTLZ2::paretoOrdinate(double x) {
    
}

double DTLZ2::getMaxDistance() const {
    
}

const char *DTLZ2::getName() {
    return "DTLZ2";
}
