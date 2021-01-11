/// Gestionnaire de films.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12
/// \modifié Maximiliano Falicoff: 2013658
/// \modifié Bryan junior Ngatshou : 1956611
/// \date 2020-04-16
#include "GestionnaireFilms.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Foncteurs.h"
#include "RawPointerBackInserter.h"
#include <vector>
#include <memory>


/// Constructeur par copie.
/// \param other    Le gestionnaire de films à partir duquel copier la classe.
GestionnaireFilms::GestionnaireFilms(const GestionnaireFilms& other)
{
    films_.reserve(other.films_.size());
    filtreNomFilms_.reserve(other.filtreNomFilms_.size());
    filtreGenreFilms_.reserve(other.filtreGenreFilms_.size());
    filtrePaysFilms_.reserve(other.filtrePaysFilms_.size());

    for (const auto& film : other.films_)
    {
        // TODO: Uncomment une fois que la fonction ajouterFilm est écrite
        ajouterFilm(*film);
    }
}

/// Opérateur d'assignation par copie utilisant le copy-and-swap idiom.
/// \param other    Le gestionnaire de films à partir duquel copier la classe.
/// \return         Référence à l'objet actuel.
GestionnaireFilms& GestionnaireFilms::operator=(GestionnaireFilms other)
{
    std::swap(films_, other.films_);
    std::swap(filtreNomFilms_, other.filtreNomFilms_);
    std::swap(filtreGenreFilms_, other.filtreGenreFilms_);
    std::swap(filtrePaysFilms_, other.filtrePaysFilms_);
    return *this;
}

/// Affiche les informations des films gérés par le gestionnaire de films à la sortie du stream donné.
/// \param outputStream         Le stream auquel écrire les informations des films.
/// \param gestionnaireFilms    Le gestionnaire de films à afficher au stream.
/// \return                     Une référence au stream.
std::ostream& operator<<(std::ostream& outputStream, const GestionnaireFilms& gestionnaireFilms)
{
    // TODO: Uncomment une fois que la fonction getNombreFilms est écrite
    outputStream << "Le gestionnaire de films contient " << gestionnaireFilms.getNombreFilms() << " films.\n"
        << "Affichage par catégories:\n";

    // TODO: Réécrire l'implémentation avec des range-based for et structured bindings (voir énoncé du TP)
    for (const auto& [key, value] : gestionnaireFilms.filtreGenreFilms_)
    {
        outputStream << "Genre: " << getGenreString(key) << " (" << value.size() << " films):\n";
        for (std::size_t i = 0; i < value.size(); i++)
        {
            outputStream << '\t' << *value[i] << '\n';
        }
    }

    return outputStream;
}

/// Ajoute les films à partir d'un fichier de description des films.
/// \param nomFichier   Le fichier à partir duquel lire les informations des films.
/// \return             True si tout le chargement s'est effectué avec succès, false sinon.
bool GestionnaireFilms::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        films_.clear();
        filtreNomFilms_.clear();
        filtreGenreFilms_.clear();
        filtrePaysFilms_.clear();

        bool succesParsing = true;

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            std::istringstream stream(ligne);

            std::string nom;
            int genre;
            int pays;
            std::string realisateur;
            int annee;

            if (stream >> std::quoted(nom) >> genre >> pays >> std::quoted(realisateur) >> annee)
            {
                // TODO: Uncomment une fois que la fonction ajouterFilm est écrite
                ajouterFilm(Film{ nom, static_cast<Film::Genre>(genre), static_cast<Pays>(pays), realisateur, annee });
            }
            else
            {
                std::cerr << "Erreur GestionnaireFilms: la ligne " << ligne
                    << " n'a pas pu être interprétée correctement\n";
                succesParsing = false;
            }
        }
        return succesParsing;
    }
    std::cerr << "Erreur GestionnaireFilms: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
    return false;
}

/**
 * @brief Ajoute un fil au gestionnaire films
 *
 * Met le film dans les trois conteneurs
 *
 * @param film
 * @return true si le film a ete correctement ajoute
 * @return false sinon
 */
bool GestionnaireFilms::ajouterFilm(const Film& film)
{
    if ((filtreNomFilms_.find(film.nom) == filtreNomFilms_.end()))
    {
        films_.push_back(std::make_unique<Film>(film));

        const Film* filmAAjouter = films_[films_.size() - 1].get();

        filtreNomFilms_.emplace(filmAAjouter->nom, filmAAjouter);
        filtreGenreFilms_[filmAAjouter->genre].push_back(filmAAjouter);
        filtrePaysFilms_[filmAAjouter->pays].push_back(filmAAjouter);

        return true;
    }

    return false;

}

/**
 * @brief Permet de supprimer un film du gestionnaire
 *
 * Supprime le film et ajuste correctement les valuers des pair dans les conteneurs
 *
 * @param nomFilm
 * @return true
 * @return false
 */
bool GestionnaireFilms::supprimerFilm(const std::string& nomFilm)
{
    auto it = filtreNomFilms_.find(nomFilm);

    if (it != filtreNomFilms_.end())
    {
        auto filmASup = getFilmParNom(nomFilm);
        auto vecteurGenre = &filtreGenreFilms_.find(filmASup->genre)->second;
        auto vecteurPays = &filtrePaysFilms_.find(filmASup->pays)->second;

        filtreNomFilms_.erase(nomFilm);
        vecteurGenre->erase(std::remove_if(vecteurGenre->begin(), vecteurGenre->end(), [nomFilm](const Film* film) {return film->nom == nomFilm; }));
        vecteurPays->erase(std::remove_if(vecteurPays->begin(), vecteurPays->end(), [nomFilm](const Film* fil) {return fil->nom == nomFilm; }));
        films_.erase(std::remove_if(films_.begin(), films_.end(), [nomFilm](std::unique_ptr<Film>& film) {return film->nom == nomFilm; }));

        return true;

    }

    return false;
}

/**
 * @brief getter du nombre de films dans le gestionnaire
 *
 * @return std::size_t le nombre de films
 */
std::size_t GestionnaireFilms::getNombreFilms() const
{
    return films_.size();
}

/**
 * @brief Permet de trouver un film dans le gstionnaire a partir du nom
 *
 * Utilise le map nom pour le trouver plus rapidement
 *
 * @param nom
 * @return const Film*
 */
const Film* GestionnaireFilms::getFilmParNom(const std::string& nom) const
{
    auto it = filtreNomFilms_.find(nom);
    return (it != filtreNomFilms_.end()) ? it->second : nullptr;

}

/**
 * @brief Permet d'avoir une liste des films d'une categorie en param
 *
 * @param genre
 * @return std::vector<const Film*> la liste des films
 */
std::vector<const Film*> GestionnaireFilms::getFilmsParGenre(Film::Genre genre) const
{
    if (filtreGenreFilms_.find(genre) == filtreGenreFilms_.end())
    {
        return {};
    }

    return filtreGenreFilms_.find(genre)->second;
}

/**
 * @brief Permet d'avoir une liste des films d'un pays en param
 *
 * @param pays
 * @return std::vector<const Film*>
 */
std::vector<const Film*> GestionnaireFilms::getFilmsParPays(Pays pays) const
{
    if (filtrePaysFilms_.find(pays) == filtrePaysFilms_.end())
    {
        return {};
    }
    return filtrePaysFilms_.find(pays)->second;
}

/**
 * @brief Permet d'avoir une l;iste de films qui sont compris entre deux annees
 *
 * @param anneeDebut
 * @param anneeFin
 * @return std::vector<const Film*> la liste de retour
 */
std::vector<const Film*> GestionnaireFilms::getFilmsEntreAnnees(int anneeDebut, int anneeFin)
{
    EstDansIntervalleDatesFilm dates(anneeDebut, anneeFin);
    std::vector<const Film*> vecteurRetour;

    RawPointerBackInserter conteneur(vecteurRetour);
    std::for_each(films_.begin(), films_.end(), [&](const std::unique_ptr<Film>& film)
        {
            if (dates.operator()(film))
            {
                conteneur.operator=(film);
            }

        });
    return vecteurRetour;

}
