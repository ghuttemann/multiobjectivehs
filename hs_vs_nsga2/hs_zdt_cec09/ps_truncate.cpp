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
#include "Solution.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

using namespace std;

#define MAXLEN	80

int main3(int argc, char **argv) {
    ParetoSet ps;
    Solution *s;
    FILE *outfile;
    FILE *infile;
    double f1, f2;
    char ofname[MAXLEN];

    /*
    char buf[MAXLEN];
    time_t now;
    struct tm *ts;
    */

    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <filename> <size>" << endl;
        return 1;
    }

    if ((infile = fopen(argv[1], "r")) != NULL) {
        while (fscanf(infile, "%le\t%le\n", &f1, &f2) > 0) {
            s = new Solution(1, 2);
            s->setObjectiveValue(0, f1);
            s->setObjectiveValue(1, f2);
            ps.add(s);
        }
    }
    else {
        cerr << "No se pudo abrir el archivo de entrada " << argv[1] << endl;
        return 1;
    }

    ps.truncate(atoi(argv[2]));

    /*
    now = time(NULL);
    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", ts);
    snprintf(ofname, MAXLEN, "pareto_%s.txt", buf);
    */
    snprintf(ofname, MAXLEN, "pareto_%d.txt", ps.getSize());
    if ((outfile = fopen(ofname, "w")) == NULL) {
        cerr << "No se pudo abrir el archivo de salida " << ofname << endl;
        return 1;
    }

    ps.print(outfile, false, false);
    fclose(outfile);
    return 0;
}
