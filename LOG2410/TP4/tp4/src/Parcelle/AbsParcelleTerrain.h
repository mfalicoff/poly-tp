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

class AbsParcelleTerrain : public AbsParcelle {
    public:
        AbsParcelleTerrain() {};
        void ajouterArrosoir(int distance);
        void recevoirArrosage(int quantiteEau);
        bool estComposite();
        int obtenirHumidite() {return m_humidite;}
        virtual void consommerEau(int quantiteEau) = 0;
    protected:
        int m_humidite;
};

#endif
