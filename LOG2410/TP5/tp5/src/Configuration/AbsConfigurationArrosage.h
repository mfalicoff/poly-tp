/****************************************************************************
**
** Classe AbsConfigurationArrosage
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef AbsConfigurationArrosage_H
#define AbsConfigurationArrosage_H

#include "../Arrosage/AbsArrosoir.h"
#include "list"

class AbsConfigurationArrosage {
    public:
        AbsConfigurationArrosage();
        int obtenirQuantiteArrosage(int debit, int duree) const;
    protected:
        virtual std::list<AbsArrosoir*> creerArrosoirs() const = 0;
        
};

#endif
