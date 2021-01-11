/****************************************************************************
**
** Classe AbsParcelle
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef ABSPARCELLE_H
#define ABSPARCELLE_H

class AbsParcelle {
    public:
        AbsParcelle();
        ~AbsParcelle();
        int getLongueurTuyeauterie();
        virtual bool estComposite() = 0;
        virtual void simulerTranspiration() = 0;
    protected:
        int m_longueurTuyeauterie;
};

#endif
