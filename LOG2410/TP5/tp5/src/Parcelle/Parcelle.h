/****************************************************************************
**
** Classe Parcelle
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef PARCELLE_H
#define PARCELLE_H

#include "AbsParcelleTerrain.h"
#include "../Configuration/AbsConfigurationArrosage.h"

class Parcelle : public AbsParcelleTerrain {
    public:
        Parcelle();
        void simulerTranspiration();
        void consommerEau(int quantite);
        void arroser(const AbsConfigurationArrosage& absConfigurationArrosage, int debit, int duree);
    private:

};

#endif
