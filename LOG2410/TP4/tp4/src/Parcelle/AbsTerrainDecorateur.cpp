/****************************************************************************
**
** Classe AbsTerrainDecorateur
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#include "AbsTerrainDecorateur.h"


void AbsTerrainDecorateur::simulerTranspiration() {
    // À COMPLÉTER
    // appeller la même méthode sur la parcelle en attribut
    m_parcelle->simulerTranspiration();
}

void AbsTerrainDecorateur::consommerEau(int quantite) {
    // À COMPLÉTER
    // appeller la même méthode sur la parcelle en attribut 
    m_parcelle->consommerEau(quantite);
}
