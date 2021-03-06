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

#ifndef HS_PARAMS_H
#define	HS_PARAMS_H

#include "HS/Params.h"

class HS_Params : public Params {
private:
    /* Harmony Memory Considering Rate */
    double hmcr;

    /* Pitch Adjusting Rate */
    double par;

    /* Overwrite problem Fret Width */
    int setFW;

    /* Real Fret Width */
    double realFW;

    /* Binary Fret Width */
    double binFW;

    /* Harmony Memory Size */
    int hms;

    /* Temporal Harmony Memory Size */
    int tmpHms;

    /* Pareto set maximum size */
    int psMaxSize;

    /* Pareto set maximum growth size */
    int psMaxGrowth;
    
    /* Minimum front size to perform truncation */
    int frontMinSize;
    
    /* Percentage to truncate when the front exceeds the minimum size */
    double truncatePercentage;

public:
    /* Constructors */
    HS_Params(const char *path);

    /* Destructor */
    ~HS_Params();
    
    /* Getters */
    int getHMS() const;
    int getTmpHMS() const;
    double getPAR() const;
    double getHMCR() const;
    int getSetFW() const;
    double getRealFW() const;
    double getBinFW() const;
    int getParetoSetMaxSize() const;
    int getParetoSetMaxGrowth() const;
    int getFrontMinSize() const;
    double getTruncatePercentage() const;
};

#endif	/* HS_PARAMS_H */
