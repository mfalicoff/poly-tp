/****************************************************************************
**
** Classe AbsArrosoir
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#ifndef ABSARROSOIR_H
#define ABSARROSOIR_H

class AbsArrosoir {
    public:
        AbsArrosoir();
        int activer(int debit, int duree);
    protected:
        // À COMPLÉTER
        // déclarer la méthode virtuelle "arroser()" qui prend en paramètre "int debit"
        virtual int arroser(int debit) = 0;
        
};

#endif
