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
    // À COMPLÉTER
    // appeller la méthode pousseeRadiculaire(), puis simulerTranspiration() de la classe parent AbsParcelleTerrain
    pousseeRadiculaire();
    m_parcelle->simulerTranspiration();
}
