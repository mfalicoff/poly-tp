// TODO: Faire l'entête de fichier

/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier Film.cpp                                        /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 28 janvier 2020 à 23h55                      /
/   Description: Implementation de la classe Film                 /
*//////////////////////////////////////////////////////////////////
// TODO: Inclure la définition de la classe appropriée
#include "Film.h"
#include "Pays.h"
#include "typesafe_enum.h"
#include <iostream>
#include <memory>

namespace {
	constexpr std::size_t CAPACITE_PAYS_INITIALE = 2;

	//! Fonction qui convertit le enum Film::Genre en string.
	//! \param genre    Le genre à convertir.
	//! \return         Le string qui représente le enum.
	const std::string& getGenreString(Film::Genre genre) {
		static const std::string NOMS_GENRES[] = { "Action", "Aventure", "Comedie",
												  "Horreur", "Romance" };

		auto index = enum_value(genre);
		assert(valid_as_enum<Pays>(index));
		return NOMS_GENRES[index];
	}

	//! Fonction qui convertit le enum Pays en string.
	//! \param pays     Le pays à convertir.
	//! \return         Le string qui représente le enum.
	const std::string& getPaysString(Pays pays) {
		static const std::string NOMS_PAYS[] = { "Bresil",     "Canada", "Chine",
												"EtatsUnis",  "France", "Japon",
												"RoyaumeUni", "Russie", "Mexique" };
		auto index = enum_value(pays);
		assert(valid_as_enum<Pays>(index));
		return NOMS_PAYS[index];
	}
} // namespace

// TODO: Constructeur par paramètre en utilisant la liste d'initialisation
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre,
	Pays pays, bool estRestreintParAge, Auteur* auteur)
	: nom_(nom), anneeDeSortie_(anneeDeSortie), genre_(genre), pays_(pays),
	estRestreintParAge_(estRestreintParAge), auteur_(auteur),
	paysRestreints_(std::make_unique<Pays[]>(CAPACITE_PAYS_INITIALE)),
	nbPaysRestreints_(0), capacitePaysRestreints_(CAPACITE_PAYS_INITIALE)
{

}
//! Méthode qui ajoute un pays à liste des pays restreints du film.
//! \param pays Pays à ajouter à la liste.

void Film::ajouterPaysRestreint(Pays pays)

// TODO fait
{
	static constexpr unsigned int AUGMENTATION_CAPACITE_PAYS = 2;

	if (capacitePaysRestreints_ < nbPaysRestreints_+1) {

		capacitePaysRestreints_ *= AUGMENTATION_CAPACITE_PAYS;         // on double la capacite

		auto test = std::make_unique<Pays[]>(capacitePaysRestreints_);  //  auto car le type T est qu<en meme assez long.

		paysRestreints_ = std::move(test);
	}

	paysRestreints_[nbPaysRestreints_] = pays;
	nbPaysRestreints_++;

}

// TODOfait : supprimerPaysRestreints()
//! Méthode qui supprime le pays restraint.
//! \aucun parametre.
void Film::supprimerPaysRestreints() {
	nbPaysRestreints_ = 0;
}

// TODO estRestreintDansPays(Pays pays) const
//! Méthode qui determine si un pays est restrain.
//! \param pays Pays.
bool Film::estRestreintDansPays(Pays pays) const {
	for (int i = 0; i <= nbPaysRestreints_; i++) {
		if (getPaysString(paysRestreints_[i]) == getPaysString(pays))  //  si le pays est passe en parametre fais partir des pays restraints.
			return true;
	}
	return false;
}

//! Méthode qui affiche le film.
//! \param stream Le stream dans lequel afficher.
void Film::afficher(std::ostream& stream) const {
	// Ne modifiez pas cette fonction
	stream << nom_ << "\n\tDate de sortie: " << anneeDeSortie_
		<< "\n\tGenre: " << getGenreString(genre_)
		<< "\n\tAuteur: " << auteur_->getNom()
		<< "\n\tPays: " << getPaysString(pays_)
		<< (nbPaysRestreints_ == 0 ? "\n\tAucun pays restreint."
			: "\n\tPays restreints:");

	for (std::size_t i = 0; i < nbPaysRestreints_; i++) {
		stream << "\n\t\t" << getPaysString(paysRestreints_[i]);
	}
	stream << '\n';
}

// TODO getGenre() const: Retourner le genre
Film::Genre Film::getGenre() const { return genre_; }

// TODO estRestreintParAge() const const: Retourner si le film est restreint par l'âge
bool Film::estRestreintParAge() const { return estRestreintParAge_; }
// TODO getNom() const: Retourner le nom du film
const std::string& Film::getNom() const { return nom_; }

// TODO getAuteur(): Retourner l'auteur du film
Auteur* Film::getAuteur() { return auteur_; }