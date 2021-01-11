/****************************************************************************
**
** Classe ArrosoirRotatif
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef ARROSOIRROTATIF_H
#define ARROSOIRROTATIF_H

#include "AbsArrosoir.h"

class ArrosoirRotatif : public AbsArrosoir {
    public:
        ArrosoirRotatif(int vitesseAngulaire);
        int arroser(int debit);
    private:
        int m_vitesseAngulaire;
};

#endif