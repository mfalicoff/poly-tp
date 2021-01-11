/****************************************************************************
**
** Classe CompositeParcelle
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef COMPOSITEPARCELLE_H
#define COMPOSITEPARCELLE_H

#include <list>
#include "AbsParcelle.h"

class CompositeParcelle : public AbsParcelle {
    public:
        void ajouterParcelle(AbsParcelle* parcelle);
        void enleverParcelle(AbsParcelle* parcelle);
        bool estComposite();
        void simulerTranspiration();
        std::list<AbsParcelle*> obtenirParcellesEnfant();

    private:
        std::list<AbsParcelle*> m_parcellesEnfants;

};

#endif
