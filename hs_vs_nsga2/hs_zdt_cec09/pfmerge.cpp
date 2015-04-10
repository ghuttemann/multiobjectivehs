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
    FILE *hsfile;
    unsigned int solutions;

    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <paretoFile> ..." << endl;
        return 1;
    }

    paretofront = new ParetoSet();
    for (int k = 1; k < argc; k++) {
        if ((hsfile = fopen(argv[k], "r")) == NULL) {
            cerr << "No se pudo abrir el archivo con el Frente Pareto: " << argv[1] << endl;
            return 1;
        }
        skipline(hsfile);
        fscanf(hsfile, "# Solutions: %d\n", &solutions);

        for (int i = 0; i < solutions; i++) {
            double obj1, obj2;

            fscanf(hsfile, "%le", &obj1);
            fscanf(hsfile, "%le", &obj2);
            ParetoPoint *p = new ParetoPoint(2);

            p->setObjectiveValue(0, obj1);
            p->setObjectiveValue(1, obj2);
            paretofront->add(p);
        }
        fclose(hsfile);
    }

    paretofront->removeDominated();
    fprintf(stdout, "# Problem: \n");
    fprintf(stdout, "# Solutions: %d\n", paretofront->getSize());
    paretofront->print(stdout, false, false);
    delete paretofront;

    return 0;
}

void skipline(FILE *f) {
    int c;

    while ((c = fgetc(f)) != '\n');
}
