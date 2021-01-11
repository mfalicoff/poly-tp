
#ifndef LIBRAIRIE_H
#define LIBRAIRIE_H

#include <memory>
#include "Film.h"
#include "GestionnaireAuteurs.h"

class Librairie
{
public:
    Librairie();
    Librairie(const Librairie& librairie);
    Librairie& operator=(const Librairie& librairie);                                                           // surcharge de l operateur=
    ~Librairie();
    Librairie& operator+=(Film* film);                                                                         // surcharge de l operateur +=
    Librairie& operator-=(std::string film);                                                                   // surcharge de l operateur -= 

    Film* chercherFilm(const std::string& nomFilm);
    bool chargerFilmsDepuisFichier(const std::string& nomFichier,
        GestionnaireAuteurs& gestionnaireAuteurs);
    bool chargerRestrictionsDepuisFichiers(const std::string& nomFichier);
    friend std::ostream& operator<<(std::ostream& stream, Librairie& librairie);                               // surcharge de l operateur << qui affiche des librairies de films
                                                                                                               // et peut etre appeler en cascade 

    const std::vector<std::unique_ptr<Film>>& getFilms() const;                                                // retourne des tableaux de films 
    std::size_t getNbFilms() const;

private:
    void supprimerFilms();
    bool lireLigneRestrictions(const std::string& ligne);
    bool lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs);
    int trouverIndexFilm(const std::string& nomFilm) const;
    std::vector<std::unique_ptr<Film>> films_;                                                                  // tableaux de films,  film en unique ptr
};

#endif // LIBRAIRIE_H