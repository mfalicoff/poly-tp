
#ifndef GESTIONNAIREAUTEURS_H
#define GESTIONNAIREAUTEURS_H

#include <string>
#include <vector>
#include "Auteur.h"
#include <vector>


class GestionnaireAuteurs
{
public:
    GestionnaireAuteurs();

    bool operator+=(Auteur auteur);                                                                       // surcharge de l operateur += qui ajoute un auteur 
    Auteur* chercherAuteur(const std::string& nomAuteur);
    bool chargerDepuisFichier(const std::string& nomFichier);
    std::vector<Auteur> getAuteurs();                                                                     //    retourne des tableaux vectors d auteurs

    friend std::ostream& operator<<(std::ostream& stream, const GestionnaireAuteurs& gestionnaireAuteur);  // surcharge de l operateur << qui affiche les tableaux d auteurs
    std::size_t getNbAuteurs() const;

    static constexpr std::size_t NB_AUTEURS_MAX = 16;                                       

private:
    bool lireLigneAuteur(const std::string& ligne);

    std::vector<Auteur> auteurs_;                                 // Tableau Vector d auteurs 
};

#endif // GESTIONNAIREAUTEURS_H