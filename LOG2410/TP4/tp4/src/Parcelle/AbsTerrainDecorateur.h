/****************************************************************************
**
** Classe AbsTerrainDecorateur
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef ABSTERRAINDECORATEUR_H
#define ABSTERRAINDECORATEUR_H

#include "AbsParcelleTerrain.h"

class AbsTerrainDecorateur : public AbsParcelleTerrain {
    public:
        AbsTerrainDecorateur(AbsParcelleTerrain* parcelle) : m_parcelle(parcelle) {}
        void simulerTranspiration();
        void consommerEau(int quantite);
    protected:
        AbsParcelleTerrain* m_parcelle;
};

#endif
