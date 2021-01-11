/****************************************************************************
**
** Classe ConfigurationArrosageA
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/


#include "ConfigurationArrosageA.h"
#include "../Arrosage/ArrosoirFixe.h"

ConfigurationArrosageA::ConfigurationArrosageA() {

}

std::list<AbsArrosoir*> ConfigurationArrosageA::creerArrosoirs() const {
    // Déjà implémenté, en guise d'exemple
    std::list<AbsArrosoir*> arrosoirs;

    ArrosoirFixe* fixe1 = new ArrosoirFixe;
    ArrosoirFixe* fixe2 = new ArrosoirFixe;

    arrosoirs.push_back(fixe1);
    arrosoirs.push_back(fixe2);

    return arrosoirs;
}
