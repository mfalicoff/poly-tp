/****************************************************************************
**
** Classe ArrosoirOscillant
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/


#include "ArrosoirOscillant.h"

ArrosoirOscillant::ArrosoirOscillant(int distance, int vitesse) {
    m_distance = distance;
    m_vitesse = vitesse;
}

int ArrosoirOscillant::arroser(int debit) {
    // À COMPLÉTER
    // retourner le débit + la distance * la vitesse
    return (debit + m_distance * m_vitesse);
}
