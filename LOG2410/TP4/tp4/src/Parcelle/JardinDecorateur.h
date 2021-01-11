/****************************************************************************
**
** Classe JardinDecorateur
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef JARDINDECORATEUR_H
#define JARDINDECORATEUR_H

#include "AbsTerrainDecorateur.h"

class JardinDecorateur : public AbsTerrainDecorateur{
    public:
        JardinDecorateur(AbsParcelleTerrain* parcelle) : AbsTerrainDecorateur(parcelle) {}
        void evapotranspirer();
        void simulerTranspiration();
        
};

#endif
