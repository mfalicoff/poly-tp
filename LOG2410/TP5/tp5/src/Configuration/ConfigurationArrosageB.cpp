/****************************************************************************
**
** Classe ConfigurationArrosageB
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/


#include "ConfigurationArrosageB.h"
#include "../Arrosage/ArrosoirFixe.h"
#include "../Arrosage/ArrosoirOscillant.h"

ConfigurationArrosageB::ConfigurationArrosageB() {

}

std::list<AbsArrosoir*> ConfigurationArrosageB::creerArrosoirs() const {
    // À COMPLÉTER
    // On veut que cette configuration contienne:
    // - un arrosoir fixe
    // - un arrosoir oscillant avec les paramètres distance = 3 et vitesse = 5
    std::list<AbsArrosoir*> arrosoirs;

    ArrosoirFixe* fixe1 = new ArrosoirFixe;
    ArrosoirOscillant* osc1 = new ArrosoirOscillant(3, 5);

    arrosoirs.push_back(fixe1);
    arrosoirs.push_back(osc1);

    return arrosoirs;
}
