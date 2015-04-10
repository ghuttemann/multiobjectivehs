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
#include <cstring>
#include <iostream>

using namespace std;

#define MAXLEN 80

void skipline(FILE *f);

int main(int argc, char **argv) {
    ParetoSet *paretofront = NULL;
    FILE *hsfile, *outfile;
    double f1min, f1max, f2min, f2max;
    char ofname[MAXLEN];
    unsigned int solutions;

    if (argc != 6) {
        cerr << "Uso: " << argv[0] << " [paretoFile] [f1min] [f1max] [f2min] [f2max]" << endl;
        return 1;
    }

    sscanf(argv[2], "%le", &f1min);
    sscanf(argv[3], "%le", &f1max);
    sscanf(argv[4], "%le", &f2min);
    sscanf(argv[5], "%le", &f2max);

    if ((hsfile = fopen(argv[1], "r")) == NULL) {
        cerr << "No se pudo abrir el archivo con el Frente Pareto del algoritmo " << argv[1] << endl;
        return 1;
    }
    skipline(hsfile);
    fscanf(hsfile, "# Solutions: %d\n", &solutions);

    paretofront = new ParetoSet();
    for (int i = 0; i < solutions; i++) {
        double obj1, obj2;

        fscanf(hsfile, "%le", &obj1);
        fscanf(hsfile, "%le", &obj2);
	if (obj1 >= f1min && obj1 <= f1max && obj2 >= f2min && obj2 <= f2max) {
            ParetoPoint *p = new ParetoPoint(2);

            p->setObjectiveValue(0, obj1);
            p->setObjectiveValue(1, obj2);
            paretofront->add(p);
	}
    }
    fclose(hsfile);

    snprintf(ofname, MAXLEN, "clean-%s", argv[1]);
    if ((outfile = fopen(ofname, "w")) == NULL) {
        cerr << "No se pudo abrir el archivo de salida " << ofname << endl;
        return 1;
    }
    fprintf(outfile, "# Problem: \n");
    fprintf(outfile, "# Solutions: %d\n", paretofront->getSize());
    paretofront->print(outfile, false, false);
    fclose(outfile);

    cout << "Se escribió exitosamente el Frente Pareto limpito.. seeee!! " << endl;
    cout << ofname << endl;
    return 0;
}

void skipline(FILE *f) {
    int c;

    while ((c = fgetc(f)) != '\n');
}
