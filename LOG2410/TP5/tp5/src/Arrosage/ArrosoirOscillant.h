/****************************************************************************
**
** Classe ArrosoirOscillant
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef ARROSOIROSCILLANT_H
#define ARROSOIROSCILLANT_H

#include "AbsArrosoir.h"

class ArrosoirOscillant : public AbsArrosoir {
    public:
        ArrosoirOscillant(int distance, int vitesse);
        int arroser(int debit);
    private:
        int m_distance;
        int m_vitesse;
};

#endif