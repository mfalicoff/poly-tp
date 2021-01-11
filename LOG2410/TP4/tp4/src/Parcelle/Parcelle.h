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

class Parcelle : public AbsParcelleTerrain {
    public:
        Parcelle();
        void simulerTranspiration();
        void consommerEau(int quantite);
    private:

};

#endif
