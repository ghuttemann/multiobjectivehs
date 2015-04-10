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

#include <cstdlib>
using namespace std;

#include "Random.h"

const int ITER = 1000000000;
const double EPSIL0 = 1e-6;
const double EPSIL1 = 1e-9;

int main(int argc, char** argv) {
    Random *random = new Random();
    int count[] = {0, 0, 0};
    double min = 1;

    for (int i=0; i < ITER; i++) {
        double num = random->random01();
        if (num < EPSIL0)
            ++count[0];

        if (num < EPSIL1)
            ++count[1];

        if (num == 0.0)
            ++count[2];

        if (num < min)
            min = num;
    }

    printf("MinVal : %e\n", min);
    printf("Total  : %d\n", ITER);
    printf("Count  : %d\n", count[0]);
    printf("Count  : %d\n", count[1]);
    printf("Count  : %d\n", count[2]);

    delete random;
    return (EXIT_SUCCESS);
}
