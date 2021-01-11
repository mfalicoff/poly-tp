/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier Film.cpp                                        /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 11 fevrier 2020 � 23h55                      /
/   Description: Implementation de la classe Utilisateur          /
*//////////////////////////////////////////////////////////////////

#include "Utilisateur.h"

//! Constructeur de la classe Utilisateur
//! \param nom          Le nom de l'utilisateur
//! \param age          L'�ge de l'utilisateur
//! \param estPremium   Bool repr�sentant si l'utilisateur est premium
//! \param pays         Pays de l'utilisateur
Utilisateur::Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays)
	: nom_(nom)
	, age_(age)
	, nbFilmsVus_(0)
	, estPremium_(estPremium)
	, pays_(pays)
{
}

//! M�thode qui retourne si le film est disponible pour un utilisateur
//! \param film Le film � �valuer
//! \return Un bool repr�sentant si un film est disponible � l'utilisateur
bool Utilisateur::filmEstDisponible(const Film& film) const
{
	static constexpr unsigned int AGE_MINIMUM_POUR_FILMS_RESTREINTS = 16;

	bool ageApproprie = true;
	if (age_ < AGE_MINIMUM_POUR_FILMS_RESTREINTS)
	{
		ageApproprie = film.estRestreintParAge() == false;
	}
	return (ageApproprie == true && film.estRestreintDansPays(pays_) == false);
}

//! M�thode qui retourne si un utilisateur a atteint le nombre limite de films qu'il peut regarder
//! \return Un bool repr�sentant si un utilisateur a atteint le nombre limite de films qu'il peut
//! regarder
bool Utilisateur::nbLimiteFilmsAtteint() const
{
	return estPremium_ == false && nbFilmsVus_ >= NB_FILMS_GRATUITS;
}

//! M�thode qui incr�mente le nombre de films vus par l'utilisateur
//! \return Un bool repr�sentant si l'utilisateur a pu regarder le film
bool Utilisateur::regarderFilm(const Film& film)
{
	if (nbLimiteFilmsAtteint() == false && filmEstDisponible(film))
	{
		nbFilmsVus_++;
		return true;
	}
	return false;
}
unsigned int Utilisateur::getNbFilmsVus() const
{
	return nbFilmsVus_;
}

