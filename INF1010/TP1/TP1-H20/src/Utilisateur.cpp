// TODO fait : Faire l'entête de fichier
/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier Utilisateur.cpp                                 /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 28 janvier 2020 à 23h55                      /
/   Description: Implementation de la classe Utilisateur          /
*//////////////////////////////////////////////////////////////////
// TODO fait : Inclure la définition de la classe appropriée
#include "Utilisateur.h"
#include <iostream>
// TODO fait : Constructeur utilisant la liste d'initialisation
Utilisateur::Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays) :
	nom_(nom), age_(age), estPremium_(estPremium), pays_(pays), nbFilmsVus_(0) {}

//! Méthode qui retourne si le film est disponible pour un utilisateur.
//! \param film Le film à évaluer.
//! \return Un bool représentant si un film est disponible à l'utilisateur.
bool Utilisateur::filmEstDisponible(const Film& film) const
{
    static constexpr unsigned int AGE_MINIMUM_POUR_FILMS_RESTREINTS = 16;
	if ( film.estRestreintParAge() && age_ < AGE_MINIMUM_POUR_FILMS_RESTREINTS) return false; // si le film est restraint par age et il  n apas l age legal
	
	if (film.estRestreintDansPays(pays_)) return false;                                       //  si le film est restraint dans le pays
	else return true;
  
}

// TODO fait: nbLimiteFilmsAtteint() const
//! Méthode qui retourne si la limite du nombre de film est atteint.
//! \param aucun.
//! \return Un bool représentant la limite du nombre de film.
bool Utilisateur:: nbLimiteFilmsAtteint() const
{
	if (estPremium_) return false;                                                  // si il est premium et qu il n a pas atteint sa limite 
	if (nbFilmsVus_ < NB_FILMS_GRATUITS && !estPremium_) return false;
	else return true;
}


// TODO fait  regarderFilm(const Film& film)
//! Méthode qui retourne si le film est regardé
//! \param film Le film à évaluer.
//! \return Un bool représentant si le film à regarder
bool Utilisateur::regarderFilm(const Film& film)
{

	if (nbLimiteFilmsAtteint() || !filmEstDisponible(film)) return false;
	nbFilmsVus_++;
	return true;
}


// TODO fait getNbFilmsVus() const: Retourner le nombre de films vus
unsigned int Utilisateur::getNbFilmsVus() const
{

	return nbFilmsVus_;
}