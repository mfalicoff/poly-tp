/****************************************************************************
**
** Classe CompositeParcelle
** Author: Fabrice Charbonneau
** Date: oct-2020
**
****************************************************************************/

#include "CompositeParcelle.h"

void CompositeParcelle::ajouterParcelle(AbsParcelle* parcelle) {
    // À COMPLÉTER
    m_parcellesEnfants.push_back(parcelle);
}

void CompositeParcelle::enleverParcelle(AbsParcelle* parcelle) {
    // À COMPLÉTER
    m_parcellesEnfants.remove(parcelle);
}

bool CompositeParcelle::estComposite() {
    return true;
}

void CompositeParcelle::simulerTranspiration() {
    std::list<AbsParcelle*>::iterator it;
    for (it = m_parcellesEnfants.begin(); it != m_parcellesEnfants.end(); ++it) {
        // À COMPLÉTER
        (*it)->simulerTranspiration();
    }
}

std::list<AbsParcelle*> CompositeParcelle::obtenirParcellesEnfant() {
    return m_parcellesEnfants;
}
