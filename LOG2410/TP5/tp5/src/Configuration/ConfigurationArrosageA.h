/****************************************************************************
**
** Classe ConfigurationArrosageA
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef ConfigurationArrosageA_H
#define ConfigurationArrosageA_H

#include "AbsConfigurationArrosage.h"

class ConfigurationArrosageA : public AbsConfigurationArrosage{
    public:
        ConfigurationArrosageA();
        std::list<AbsArrosoir*> creerArrosoirs() const override;
};

#endif
