/****************************************************************************
**
** Classe ConfigurationArrosageC
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef ConfigurationArrosageC_H
#define ConfigurationArrosageC_H

#include "AbsConfigurationArrosage.h"

class ConfigurationArrosageC : public AbsConfigurationArrosage{
    public:
        ConfigurationArrosageC();
        std::list<AbsArrosoir*> creerArrosoirs() const override;
};

#endif
