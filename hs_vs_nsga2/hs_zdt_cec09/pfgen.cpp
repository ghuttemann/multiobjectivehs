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

#include "BitFieldVariableBuilder.h"
#include "ParetoSet.h"
#include "Problem.h"
#include "RealVariableBuilder.h"
#include "CEC09UnProb1.h"
#include "CEC09UnProb2.h"
#include "CEC09UnProb3.h"
#include "CEC09UnProb4.h"
#include "CEC09UnProb5.h"
#include "ZDT1.h"
#include "ZDT2.h"
#include "ZDT3.h"
#include "ZDT4.h"
#include "ZDT5.h"
#include "ZDT6.h"
#include "HS_Params.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

#define MAXLEN 80

int main(int argc, char **argv) {
    ParetoSet *ps = NULL;
    Problem *problem = NULL;
    FILE *outfile;
    char ofname[MAXLEN];
    char path[MAXLEN]  = "../../datos/test_problems/";
    char path2[MAXLEN];

    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " [zdt1|zdt2|zdt3|zdt4|zdt5|zdt6|"
                "cec09unprob1|cec09unprob2|cec09unprob3|cec09unprob4|cec09unprob5]" << endl;
        return 1;
    }

    /* Inicializar parámetros HS */
    strcpy(path2, path);
    HS_Params *hsParams = new HS_Params(strcat(path2, "hs_config.txt"));

    if (strcasecmp(argv[1], "zdt1") == 0)
        problem = new ZDT1(strcat(path, "zdt/zdt1.txt"),
                hsParams, new RealVariableBuilder());
    else if (strcasecmp(argv[1], "zdt2") == 0)
        problem = new ZDT2(strcat(path, "zdt/zdt2.txt"),
                hsParams, new RealVariableBuilder());
    else if (strcasecmp(argv[1], "zdt3") == 0)
        problem = new ZDT3(strcat(path, "zdt/zdt3.txt"),
                hsParams, new RealVariableBuilder());
    else if (strcasecmp(argv[1], "zdt4") == 0)
        problem = new ZDT4(strcat(path, "zdt/zdt4.txt"),
                hsParams, new RealVariableBuilder());
    else if (strcasecmp(argv[1], "zdt5") == 0)
        problem = new ZDT5(strcat(path, "zdt/zdt5.txt"),
                hsParams, new BitFieldVariableBuilder());
    else if (strcasecmp(argv[1], "zdt6") == 0)
        problem = new ZDT6(strcat(path, "zdt/zdt6.txt"),
                hsParams, new RealVariableBuilder());
    else if (strcasecmp(argv[1], "cec09unprob1") == 0)
        problem = new CEC09UnProb1(strcat(path, "cec09/cec09unprob1.txt"),
                hsParams, new RealVariableBuilder());
    else if (strcasecmp(argv[1], "cec09unprob2") == 0)
        problem = new CEC09UnProb2(strcat(path, "cec09/cec09unprob2.txt"),
                hsParams, new RealVariableBuilder());
    else if (strcasecmp(argv[1], "cec09unprob3") == 0)
        problem = new CEC09UnProb3(strcat(path, "cec09/cec09unprob3.txt"),
                hsParams, new RealVariableBuilder());
    else if (strcasecmp(argv[1], "cec09unprob4") == 0)
        problem = new CEC09UnProb4(strcat(path, "cec09/cec09unprob4.txt"),
                hsParams, new RealVariableBuilder());
    else if (strcasecmp(argv[1], "cec09unprob5") == 0)
        problem = new CEC09UnProb5(strcat(path, "cec09/cec09unprob5.txt"),
                hsParams, new RealVariableBuilder());
    else {
        cerr << argv[0] << ": Problema no válido." << endl <<
                "Opciones: zdt1, zdt2, zdt3, zdt4, zdt5, zdt6, "
                "cec09unprob1, cec09unprob2, cec09unprob3, cec09unprob4, cec09unprob5" << endl;
        return 1;
    }

    ps = problem->optimalParetoFront();
    if (ps == NULL) {
        cerr << argv[0] << ": Ocurrió un problema al generar el Y_true." << endl;
        return 1;
    }
    /*
    now = time(NULL);
    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", ts);
    snprintf(ofname, MAXLEN, "pareto_%s.txt", buf);
    */
    snprintf(ofname, MAXLEN, "ytrue-%s-%d.txt", argv[1], ps->getSize());
    if ((outfile = fopen(ofname, "w")) == NULL) {
        cerr << "No se pudo abrir el archivo de salida " << ofname << endl;
        return 1;
    }

    fprintf(outfile, "# Problem: %s\n", argv[1]);
    fprintf(outfile, "# Solutions: %d\n", ps->getSize());
    ps->print(outfile, false, false);
    fclose(outfile);

    delete problem;
    delete ps;
    return 0;
}
