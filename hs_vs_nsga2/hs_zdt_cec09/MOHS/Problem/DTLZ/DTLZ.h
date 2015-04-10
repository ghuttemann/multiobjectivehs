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

#ifndef DTLZ_H
#define DTLZ_H

#include "Problem/Problem.h"
#include "Variable/RealVariable.h"
#include "HS/HS_Params.h"

class DTLZ : public Problem {
private:
    /* Value of K = N - M + 1 (number of variables in partition M) */
    int k;
    
    /* List of functions values*/
    double *f;
    
protected:
    static const double PI = 3.14159265358979;
    
    /* Calculates values of objectives functions and sets into f array */
    virtual void calculate_f(const Solution *sol, double g, double *f) = 0;
    
    /* Calculates value of g function */
    virtual double calculate_g(const Solution *sol) = 0;
    
    /* Get value of K */
    int getK() const;
    
    /* Get value of M */
    int getM() const;
    
    /* Get value of N */
    int getN() const;
    
public:
    DTLZ(int objectives, const char *path, HS_Params *hsParams, VariableBuilder *varBuilder);
    
    /** Pure virtual destructor (abstract class). */
    virtual ~DTLZ() = 0;
    
    /** Evaluation function. */
    void evaluate(Solution *sol);
    
    /** Just for compatibility */
    ParetoSet *optimalParetoFront(void);
};

#endif
