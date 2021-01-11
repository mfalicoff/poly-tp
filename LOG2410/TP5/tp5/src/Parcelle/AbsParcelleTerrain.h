/****************************************************************************
**
** Classe AbsParcelleTerrain
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef ABSPARCELLETERRAIN_H
#define ABSPARCELLETERRAIN_H

#include <list>
#include "AbsParcelle.h"
#include "../Arrosage/AbsArrosoir.h"

class AbsParcelleTerrain : public AbsParcelle {
    public:
        AbsParcelleTerrain() {};
        void recevoirArrosage(int quantiteEau);
        bool estComposite();
        int obtenirHumidite() {return m_humidite;}
        virtual void consommerEau(int quantiteEau) = 0;
        int m_humidite;
};

#endif
