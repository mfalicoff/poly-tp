/****************************************************************************
**
** Classe AbsParcelleTerrain
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#include "AbsArrosoir.h"

AbsArrosoir::AbsArrosoir() {}

int AbsArrosoir::activer(int debit, int duree) {
    // À COMPLÉTER
    // d'abord, déclarer la méthode virtuelle "arroser(debit)" dans AbsArrosoir.h
    // appeller la méthode virtuelle "arroser(debit)", et multiplier ce résultat par "duree"
    // retourner le résultat final
    return arroser(debit)* duree;
}
