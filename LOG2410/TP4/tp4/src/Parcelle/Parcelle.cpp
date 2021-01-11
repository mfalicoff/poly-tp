/****************************************************************************
**
** Classe Parcelle
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#include "Parcelle.h"

Parcelle::Parcelle() {
    m_humidite = 100;
}

void Parcelle::simulerTranspiration() {
    consommerEau(10);
}

void Parcelle::consommerEau(int quantite) {
    m_humidite -= quantite;
}
