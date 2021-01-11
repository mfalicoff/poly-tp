/****************************************************************************
**
** Classe JardinDecorateur
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/


#include "JardinDecorateur.h"

void JardinDecorateur::evapotranspirer() {
    this->m_parcelle->consommerEau(5);
}
void JardinDecorateur::simulerTranspiration() {
    // À COMPLÉTER
    // appeller la méthode evapotranspirer(), puis simulerTranspiration() de la classe parent AbsTerrainDecorateur
    evapotranspirer();
    m_parcelle->simulerTranspiration();
}

