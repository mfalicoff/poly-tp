/****************************************************************************
**
** Classe ArrosoirRotatif
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#include "ArrosoirRotatif.h"

ArrosoirRotatif::ArrosoirRotatif(int vitesseAngulaire) {
    m_vitesseAngulaire = vitesseAngulaire;

}

int ArrosoirRotatif::arroser(int debit) {
    // À COMPLÉTER
    // retourner le débit * la vitesse angulaire
    return debit * m_vitesseAngulaire;
}
