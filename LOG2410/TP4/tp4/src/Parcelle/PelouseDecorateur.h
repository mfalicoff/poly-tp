/****************************************************************************
**
** Classe PelouseDecorateur
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef PELOUSEDECORATEUR_H
#define PELOUSEDECORATEUR_H

#include "AbsTerrainDecorateur.h"

class PelouseDecorateur : public AbsTerrainDecorateur{
    public:
        PelouseDecorateur(AbsParcelleTerrain* parcelle, int facteurRadiculaire) :
        AbsTerrainDecorateur(parcelle),
        m_facteurRadiculaire(facteurRadiculaire)
        {}
        void pousseeRadiculaire();
        void simulerTranspiration();
    private:
        int m_facteurRadiculaire;
        
};

#endif