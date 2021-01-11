/****************************************************************************
**
** Classe AbsTerrainDecorateur
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#include "AbsTerrainDecorateur.h"


void AbsTerrainDecorateur::simulerTranspiration() {
    this->m_parcelle->simulerTranspiration();
}

void AbsTerrainDecorateur::consommerEau(int quantite) {
    this->m_parcelle->consommerEau(quantite);
}
