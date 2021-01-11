/****************************************************************************
**
** Classe PelouseDecorateur
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/


#include "PelouseDecorateur.h"


void PelouseDecorateur::pousseeRadiculaire() {
    this->m_parcelle->consommerEau(m_facteurRadiculaire);
}

void PelouseDecorateur::simulerTranspiration() {
    this->pousseeRadiculaire();
    AbsTerrainDecorateur::simulerTranspiration();
}
