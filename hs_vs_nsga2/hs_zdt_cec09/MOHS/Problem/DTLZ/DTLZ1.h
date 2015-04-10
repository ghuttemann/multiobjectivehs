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

#ifndef DTLZ1_H
#define DTLZ1_H

#include "Problem/DTLZ/DTLZ.h"
#include "Variable/RealVariable.h"
#include "HS/HS_Params.h"

class DTLZ1 : public DTLZ {
public:
    /** Constructor. */
    DTLZ1(int m, const char *path, HS_Params *hsParams, VariableBuilder *varBuilder);
    
    /** Destructor. */
    ~DTLZ1();
    
    /** Just for compatibility */
    double paretoOrdinate(double x);
    double getMaxDistance() const;
    
    /* Calculates values of objectives functions and sets into f array */
    void calculate_f(const Solution *sol, double g, double *f);
    
    /* Calculates value of g function */
    double calculate_g(const Solution *sol);
    
    /** Problem name. */
    const char *getName();
};

#endif
