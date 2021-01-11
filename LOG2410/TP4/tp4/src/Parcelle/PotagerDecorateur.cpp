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
    // À COMPLÉTER
    // appeller la méthode remonteeCapillaire(), puis simulerTranspiration() de la classe parent AbsParcelleTerrain
    remonteeCapillaire();
    m_parcelle->simulerTranspiration();
}
