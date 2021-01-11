/****************************************************************************
**
** Classe AbsParcelleTerrain
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#include "AbsParcelleTerrain.h"


void AbsParcelleTerrain::recevoirArrosage(int quantiteEau) {
    this->m_humidite += quantiteEau;
}

bool AbsParcelleTerrain::estComposite() {
    return false;
}
