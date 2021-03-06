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

#include "ParetoSet.h"
#include "ParetoPoint.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#define MAXLEN 80

void skipline(FILE *f);

int main(int argc, char **argv) {
    ParetoSet *paretofront = NULL;
    ParetoSet *ytrue = NULL;
    FILE *hsfile, *ytruefile;
    unsigned int solutions;
    double absM1, absM2, absM3;
    double normM1, normM2, normM3;
    double error, igd;

    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " [paretoFile] [ytrueFile]" << endl;
        return 1;
    }

    if ((hsfile = fopen(argv[1], "r")) == NULL) {
        cerr << argv[0] << ": No se pudo abrir el archivo con el Frente Pareto del algoritmo " << argv[1] << endl;
        return 1;
    }
    skipline(hsfile);
    fscanf(hsfile, "# Solutions: %d\n", &solutions);

    paretofront = new ParetoSet();
    for (int i = 0; i < solutions; i++) {
        double obj1, obj2;
        ParetoPoint *p = new ParetoPoint(2);

        fscanf(hsfile, "%le", &obj1);
        fscanf(hsfile, "%le", &obj2);
        p->setObjectiveValue(0, obj1);
        p->setObjectiveValue(1, obj2);
        paretofront->add(p);
    }
    fclose(hsfile);

    if ((ytruefile = fopen(argv[2], "r")) == NULL) {
        cerr << argv[0] << ": No se pudo abrir el archivo con el Y_true " << argv[2] << endl;
        return 1;
    }
    skipline(ytruefile);
    fscanf(ytruefile, "# Solutions: %d\n", &solutions);
    ytrue = new ParetoSet();
    for (int i = 0; i < solutions; i++) {
        double obj1, obj2;
        ParetoPoint *p = new ParetoPoint(2);

        fscanf(ytruefile, "%le", &obj1);
        fscanf(ytruefile, "%le", &obj2);
        p->setObjectiveValue(0, obj1);
        p->setObjectiveValue(1, obj2);
        ytrue->add(p);
    }
    fclose(ytruefile);

    absM1 = paretofront->metricM1(ytrue);
    absM2 = paretofront->metricM2();
    absM3 = paretofront->metricM3();
    
    normM1 = absM1;
    normM2 = absM2 / paretofront->getSize();
    normM3 = absM3 / ytrue->metricM3();

    error = paretofront->metricError(ytrue);
    igd   = ytrue->metricM1(paretofront);
    
    printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\n", absM1, normM1, absM2, normM2,
        absM3, normM3, error, igd, paretofront->getSize());
            
    delete paretofront;
    delete ytrue;

    return 0;
}

void skipline(FILE *f) {
    int c;

    while ((c = fgetc(f)) != '\n');
}
