/****************************************************************************
**
** Classe ConfigurationArrosageB
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef ConfigurationArrosageB_H
#define ConfigurationArrosageB_H

#include "AbsConfigurationArrosage.h"

class ConfigurationArrosageB : public AbsConfigurationArrosage{
    public:
        ConfigurationArrosageB();
        std::list<AbsArrosoir*> creerArrosoirs() const override;
};

#endif
