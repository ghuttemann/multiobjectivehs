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

#include "Problem/DTLZ/DTLZ.h"
#include "VariableBuilder/RealVariableBuilder.h"
#include <cmath>

DTLZ::DTLZ(int m, const char *path, HS_Params *hsParams,
        VariableBuilder *varBuilder) : Problem(varBuilder) {
    
    FILE *file;

    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file '%s' in read mode\n", path);
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &k);
    objectives = m;
    size = objectives + k - 1;
    f = new double[objectives];
    
    minimum = new Variable*[size];
    maximum = new Variable*[size];
    fretWidth = new Variable*[size];
    
    double min, max, fw;
    fscanf(file, "%lf", &min);
    fscanf(file, "%lf", &max);
    fscanf(file, "%lf", &fw);
    
    fclose(file);
    
    for (int i=0; i < size; i++) {
        minimum[i]   = ((RealVariableBuilder *) varBuilder)->createVariable(min);
        maximum[i]   = ((RealVariableBuilder *) varBuilder)->createVariable(max);
        fretWidth[i] = ((RealVariableBuilder *) varBuilder)->createVariable(fw);
    }

    if (hsParams->getSetFW() == 1) {
        for (int i=0; i < size; i++) {
            RealVariable *r1 = (RealVariable *) minimum[i];
            RealVariable *r2 = (RealVariable *) maximum[i];
            
            double width = r2->getValue() - r1->getValue();
            double value = hsParams->getRealFW() * width / 100.0;

            delete fretWidth[i];
            fretWidth[i] = ((RealVariableBuilder *) varBuilder)->createVariable(value);
        }
    }
}

DTLZ::~DTLZ() {
    for (int i=0; i < size; i++) {
        delete minimum[i];
        delete maximum[i];
        delete fretWidth[i];
    }

    delete[] minimum;
    delete[] maximum;
    delete[] fretWidth;
    
    delete[] f;
}

int DTLZ::getK() const {
    return k;
}

int DTLZ::getM() const {
    return this->getObjectives();
}

int DTLZ::getN() const {
    return this->getSize();
}

void DTLZ::evaluate(Solution *sol) {
    double g = this->calculate_g(sol);
    this->calculate_f(sol, g, this->f);
    
    for (int i=0; i < this->objectives; i++)
        sol->setObjectiveValue(0, this->f[i]);
}

ParetoSet *DTLZ::optimalParetoFront(void) {
    
}
