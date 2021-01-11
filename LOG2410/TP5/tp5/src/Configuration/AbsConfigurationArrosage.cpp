/****************************************************************************
**
** Classe AbsConfigurationArrosage
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#include "AbsConfigurationArrosage.h"

AbsConfigurationArrosage::AbsConfigurationArrosage() {}

// fonctions permettant de delete les éléments d'une liste
// tiré de https://stackoverflow.com/questions/307082/cleaning-up-an-stl-list-vector-of-pointers
static bool deleteAll(AbsArrosoir * arrosoir ) { 
    delete arrosoir; 
    return true; 
}

static void deleteListeArrosoirs(std::list<AbsArrosoir*> arrosoirs) {
    arrosoirs.remove_if(deleteAll);
}

int AbsConfigurationArrosage::obtenirQuantiteArrosage(int debit, int duree) const {

    // À COMPLÉTER
    // créer les arrosoirs en utilisant la méthode virtuelle qui sera implémentée dans les enfants de AbsConfigurationArrosage
    std::list<AbsArrosoir*> arrosoirs = creerArrosoirs();

    // calculer le total d'arrosage en utilisant la fonction activer() sur chaque arrosoir de la liste créée
    int totalArrosage = 0;
    for (AbsArrosoir* arrosoir: arrosoirs) {
        // À COMPLÉTER
        totalArrosage += arrosoir->activer(debit, duree);
    }

    // À COMPLÉTER
    // delete la liste en utilisant deleteListeArrosoirs
    deleteListeArrosoirs(arrosoirs);

    // retourner le résultat
    return totalArrosage;
}
