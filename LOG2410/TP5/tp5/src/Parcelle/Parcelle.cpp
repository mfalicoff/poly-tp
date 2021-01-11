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

void Parcelle::arroser(const AbsConfigurationArrosage& absConfigurationArrosage, int debit, int duree) {
    // À COMPLÉTER
    // ajouter à m_humidite la quantite d'arrosage obtenue avec absConfigurationArrosage
    m_humidite += absConfigurationArrosage.obtenirQuantiteArrosage(debit, duree);
}

void Parcelle::simulerTranspiration() {
    consommerEau(10);
}

void Parcelle::consommerEau(int quantite) {
    m_humidite -= quantite;
}
