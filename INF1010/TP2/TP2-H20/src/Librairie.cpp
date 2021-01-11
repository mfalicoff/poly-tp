/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier Film.cpp                                        /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 11 fevrier 2020 � 23h55                      /
/   Description: Implementation de la classe Librairie            /
*//////////////////////////////////////////////////////////////////

#include "Librairie.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "debogageMemoire.h"
#include "typesafe_enum.h"

namespace
{
    constexpr std::size_t CAPACITE_FILMS_INITIALE = 2;
    constexpr int FILM_INEXSISTANT = -1;
} // namespace

// constructeur par defaut
Librairie::Librairie()
{
}
//! Constructeur par copie de la classe  Librairie
Librairie::Librairie(const Librairie& librairie)
{
    films_.clear();
    for (int i = 0; i < librairie.films_.size(); i++)
    {
        auto ajout = std::make_unique<Film>(*(librairie.films_[i]));              
        films_.push_back(std::move(ajout));
    }
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    supprimerFilms();                                         // utilisation de la methode supprimerFilms();
}

const std::vector<std::unique_ptr<Film>>& Librairie::getFilms() const
{
    return films_;
}

//! M�thode qui retire un film � la liste des films grace a une surcharge de l operateur -=
//! \param film Le film allou� dynamiquement � ajouter � la liste. La classe devient propri�taire du
//!             film.
Librairie& Librairie ::operator-=(std::string film)
{
    int pos = trouverIndexFilm(film);
    if (pos != FILM_INEXSISTANT)
    {
        films_[pos]->~Film();
        films_[pos] = move(films_[films_.size() - 1]);
        films_.pop_back();
    }

    return *this;                                                          // utilisation du mot cle *this; on retourne la valeur point� dans la librairie
}

//! M�thode qui ajoute un film de la liste grace a une surcharge de l operateur +=
//! \param nomFilm Le nom du film � retirer
// retour : pointeur *this dans la librairie
Librairie& Librairie::operator+=(Film* film)

{
    if (film != nullptr)
    {
        std::unique_ptr<Film> test;
        test.reset(film);
        films_.push_back(std::move(test));
        return *this;                                                     // utilisation du mot cle *this; on retourne la valeur point� dans la librairie
    }
}

//! M�thode qui ecrase les film par la liste des films qui est passee en parametre. 
//! \param librairie qui remplace la liste existante
//  retour : un pointeur sur la *this sur la  variable que pointe la librairie( les films) 

Librairie& Librairie ::operator=(const Librairie& librairie)
{
    if (this != &librairie)
    {
        films_.clear();

        for (size_t i = 0; i < librairie.films_.size(); i++)
        {
            auto filmptr = std::make_unique<Film>(*librairie.films_[i]);
            films_.push_back(std::move(filmptr));
        }

    }

    return *this;
}

//! M�thode qui retourne un film comportant le m�me nom que celui envoy� en param�tre
//! \param nomFilm Le nom du film � chercher
//! \return        Un pointeur vers le film. Nullptr si le film n'existe pas
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    int indexFilm = trouverIndexFilm(nomFilm);
    if (indexFilm == FILM_INEXSISTANT)
    {
        return nullptr;
    }

    return films_[indexFilm].get();
}

//! M�thode qui charge les films � partir d'un fichier.
//! \param nomFichier           Le nom du fichier � lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. N�cessaire pour associer un film � un
//! auteur.
//! \return                     Un bool repr�sentant si le chargement a �t� un succ�s.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
    GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // Supprimer les vieux films avant de lire les nouveaux
        supprimerFilms();

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneFilm(ligne, gestionnaireAuteurs) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
        << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! M�thode qui charge les restrictions des films � partir d'un fichier.
//! \param nomFichier           Le nom du fichier � lire.
//! \return                     Un bool repr�sentant si le chargement a �t� un succ�s.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (std::size_t i = 0; i < films_.size(); i++)
        {
            films_[i]->supprimerPaysRestreints();
        }
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneRestrictions(ligne) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
        << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! M�thode qui affiche la liste des films grace a une surcharge de l operateur <<.
//! \param stream Le stream dans lequel afficch� et la liste des films a afficher
//  retourne le stream.
std::ostream& operator<<(std::ostream& stream, Librairie& librairie)
{
    for (std::size_t i = 0; i < librairie.getFilms().size(); i++)
    {
        stream << *librairie.films_[i];
        stream << '\n';
    }
    return stream;
}

//! M�thode qui retourne le nombre de films
//! \return Le nombre de films
std::size_t Librairie::getNbFilms() const
{
    return films_.size();
}

//! M�thode qui supprime tous les films
void Librairie::supprimerFilms()
{
    films_.clear();
}

//! M�thode qui ajoute les restrictions d'un film avec un string
//! \param ligne Le string comportant les restrictions du film
//! \return      Un bool repr�sentant si l'op�ration est un succ�s
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    if (stream >> std::quoted(nomFilm))
    {
        auto film = chercherFilm(nomFilm);
        if (film == nullptr)
        {
            // Film n'existe pas
            return false;
        }

        int paysValeurEnum;
        while (stream >> paysValeurEnum)
        {
            film->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
        }
        return true;
    }
    return false;
}

//! M�thode qui ajoute un film avec un string comportant les attributs du film
//! \param ligne                Le string comportant les attributs du film
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. N�cessaire pour associer un film � un
//!                             auteur.
//! \return                     Un bool repr�sentant si l'op�ration est un succ�s
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;

    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)

    if (stream >> std::quoted(nomFilm) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >>
        estRestreintParAge >> std::quoted(nomAuteur))
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        auteur->setNbFilms(auteur->getNbFilms() + 1);
        Film* film = new Film(nomFilm,
            anneeSortie,
            to_enum<Film::Genre>(genreValeurEnum),
            to_enum<Pays>(paysValeurEnum),
            estRestreintParAge,
            auteur);
        operator+=(film);
        return true;
    }
    return false;
}

//! M�thode qui retourne l'index d'un film en cherchant son nom
//! \param nomFilm Le nom du film � trouver
//! \return        L'index du film. Retourne -1 si le film n'existe pas
int Librairie::trouverIndexFilm(const std::string& nomFilm) const
{
    for (std::size_t i = 0; i < films_.size(); i++)
    {
        if (films_[i]->getNom() == nomFilm)
        {
            return (int)i;
        }
    }
    return FILM_INEXSISTANT;
}