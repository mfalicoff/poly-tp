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
    this->evapotranspirer();
    AbsTerrainDecorateur::simulerTranspiration();
}

