/****************************************************************************
**
** Classe PotagerDecorateur
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef POTAGERDECORATEUR_H
#define POTAGERDECORATEUR_H


#include "AbsTerrainDecorateur.h"

class PotagerDecorateur : public AbsTerrainDecorateur{
    public:
        PotagerDecorateur(AbsParcelleTerrain* parcelle, int nPlantes) : 
        AbsTerrainDecorateur(parcelle),
        m_nPlantes(nPlantes)
        {}
        void remonteeCapillaire();
        void simulerTranspiration();
    private:
        int m_nPlantes;
};

#endif
