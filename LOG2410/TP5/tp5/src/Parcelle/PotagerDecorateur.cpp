/****************************************************************************
**
** Classe PotagerDecorateur
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/


#include "PotagerDecorateur.h"

void PotagerDecorateur::remonteeCapillaire() {
    this->m_parcelle->consommerEau(5*m_nPlantes);
}

void PotagerDecorateur::simulerTranspiration() {
    this->remonteeCapillaire();
    AbsTerrainDecorateur::simulerTranspiration();
}
