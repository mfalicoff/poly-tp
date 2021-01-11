

// TODO: Faire l'entête de fichier
/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier Librairie.cpp                                   /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 28 janvier 2020 à 23h55                      /
/   Description: Implementation de la classe Librairie            /
*//////////////////////////////////////////////////////////////////
// TODO: Inclure la définition de la classe appropriée
#include "debogageMemoire.h"
#include "typesafe_enum.h"
#include <Pays.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "Librairie.h"


namespace {
	constexpr std::size_t CAPACITE_FILMS_INITIALE = 2;
	constexpr int FILM_INEXSISTANT = -1;
} // namespace

// TODO fait : Constructeur par défault en utilisant la liste d'initialisation

Librairie::Librairie() : nbFilms_(0), capaciteFilms_(CAPACITE_FILMS_INITIALE)
{

	films_ = new Film * [capaciteFilms_];

}

// TODO fait : Destructeur
Librairie::~Librairie() {
	supprimerFilms();            
	delete[] films_;      //  on supprime le tableau ( delete [])
	films_ = nullptr;      //  on desalloue le tableau ( nullptr)
}

//! Méthode qui ajoute un film à la liste des films.
//! \param film Le film alloué dynamiquement à ajouter à la liste. La classe
//! devient propriétaire du
//!             film.
void Librairie::ajouterFilm(Film* film) {
	static constexpr unsigned int AUGMENTATION_CAPACITE_FILMS = 2;

	// TODO fait : 


	if (capaciteFilms_ < nbFilms_ + 1)
	{

		capaciteFilms_ = capaciteFilms_ * AUGMENTATION_CAPACITE_FILMS;  // on cree un autre tableau de film de capacite
		Film** test = new Film * [capaciteFilms_];                     // deux fois plus grande


		for (std::size_t i = 0; i < capaciteFilms_ / AUGMENTATION_CAPACITE_FILMS; i++) {
			test[i] = films_[i];                                         // on transfert les donnees de film dans le nouveau tableau
		}

		for (size_t i = capaciteFilms_ / AUGMENTATION_CAPACITE_FILMS; i < capaciteFilms_; i++)
		{
			test[i] = nullptr;                                           // on desalloue Films_
		}



		delete[] films_;
		films_ = test;                                                   // et on retransfere les donnes du nouveau film a l ancien
		                                                                 // *damn*

	}

	if (film != nullptr)
	{
		films_[nbFilms_] = film;
		Auteur* auteur = films_[nbFilms_]->getAuteur();           //  on ajoute le nouveau film.
		auteur->setNbFilms(auteur->getNbFilms() + 1);
		nbFilms_++;

	}

}

// TODO fait : retirerFilm(const std::string& nomFilm
//! Méthode qui retire un film dans la liste des films.
//! \param nom du film à retirer.

void Librairie::retirerFilm(const std::string& nomFilm) {

	int i = trouverIndexFilm(nomFilm);

	if (i != -1) {
		delete films_[i];						// On doit delete l'objet en heap sinon va causer un mem leak
		films_[i] = films_[nbFilms_ - 1];       // si le film possede est dans la liste des films, on le met en derniere position
		films_[nbFilms_ - 1] = nullptr;         // ensuite on le supprime (on desalloue sa place(nullptr))
		nbFilms_--;                             // on diminue le nbre de films.

	}
}

// TODO fait :: chercherFilm(const std::string& nomFilm)
//! Méthode qui cherche un film dans la liste des films.
//! \param nom du film à chercher

Film* Librairie::chercherFilm(const std::string& nomfilm) {
	int index = trouverIndexFilm(nomfilm);
	if (index != -1) return films_[index];
	else return nullptr;
}

//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour
//! associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si le chargement a été un
//! succès.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
	GestionnaireAuteurs& gestionnaireAuteurs)
{
	std::ifstream fichier(nomFichier);
	if (fichier)                                //     si le fichier est ouvert
	{
		// TODO
		for (int i = 0; i < nbFilms_; i++)
		{
			(films_[i]->getAuteur())->setNbFilms(0);
		}
		supprimerFilms();                                  // on supprime les films existants (les nullptr je suppose)
		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			if (!lireLigneFilm(ligne, gestionnaireAuteurs))return false;
			
		}
		return true;
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
	return false;
}



//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un
//! succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		// TODO
		for (int i = 0; i < nbFilms_; i++)
		{
			films_[i]->supprimerPaysRestreints();
		}
		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			if (!lireLigneRestrictions(ligne))
			
			{
				return false;
			}
		}
		return true;
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
	return false;
}


//! Méthode qui affiche la liste des films.
//! \param stream Le stream dans lequel afficher.
void Librairie::afficher(std::ostream& stream) const {
	// Ne pas modifier cette méthode
	for (std::size_t i = 0; i < nbFilms_; i++) {
		films_[i]->afficher(stream);
		stream << '\n';
	}
}

// TODO getNbFilms() const: Retourner le nombre de films
std::size_t Librairie::getNbFilms() const { return nbFilms_; }

// TODO fait: supprimerFilms()
void Librairie::supprimerFilms() {
	for (size_t i = 0; i < nbFilms_; i++) {
		delete films_[i];
		films_[i] = nullptr;
	}
	nbFilms_ = 0;
}
//  methode qui permet de lir eles lignes de restrictions dans un fichier.
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomFilm;
	// TODO fait :  
	int paysValeurEnum;
	stream >> std::quoted(nomFilm);
	int index = trouverIndexFilm(nomFilm);
	if (index != -1)
	{
		while (stream >> paysValeurEnum)
		{
			films_[index]->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
		}

		return true;
	}
	return false;
}
//! Méthode qui ajoute un film avec un string comportant les attributs du film.
//! \param ligne                Le string comportant les attributs du film.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès.
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
	std::istringstream stream(ligne);
	std::string nomFilm;
	unsigned int anneeSortie;
	int genreValeurEnum;
	int paysValeurEnum;
	bool estRestreintParAge;
	std::string nomAuteur;
	stream >> std::quoted(nomFilm) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >> estRestreintParAge >> std::quoted(nomAuteur);
	Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
	if (auteur == nullptr) return false;


	Film* nouveauFilm = new Film(nomFilm, anneeSortie, to_enum<Film::Genre>(genreValeurEnum), to_enum<Pays>(paysValeurEnum),
		estRestreintParAge, auteur);
	ajouterFilm(nouveauFilm);                  //Pas sûr de savoir pourquoi...
	
	return true;
}

// TODO  fait : trouverIndexFilm(const std::string& nomFilm) const
//! Méthode qui trouve l'index d'un Film.
//! \param pays Pays à ajouter à la liste.
int Librairie::trouverIndexFilm(const std::string& nomFilm) const {            
	for (int i = 0; i < nbFilms_; i++) {
		if (films_[i]->getNom() == nomFilm)            //  si le nom du film se trouve dans la liste des films.
			return i;
	}
	return -1;
}