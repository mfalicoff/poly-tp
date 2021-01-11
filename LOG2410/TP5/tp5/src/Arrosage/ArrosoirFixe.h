/****************************************************************************
**
** Classe ArrosoirFixe
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef ARROSOIRFIXE_H
#define ARROSOIRFIXE_H

#include "AbsArrosoir.h"

class ArrosoirFixe : public AbsArrosoir {
    public:
        ArrosoirFixe();
        int arroser(int debit);
    private:

};

#endif
