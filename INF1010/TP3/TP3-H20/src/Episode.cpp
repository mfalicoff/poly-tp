/* ////////////////////////////////////////////////////////////////
/	TD3 : fichier Episode.cpp                                     /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 11 fevrier 2020 � 23h55                      /
/   Description: Implementation de la classe Episode              /
*//////////////////////////////////////////////////////////////////

#include "Episode.h"

//! Constructeur de la classe Episode default
Episode::Episode()
{
	nom_ = "";
	duree_ = "";
	numEpisode_ = 0;
}

//! Constructeur de la classe Auteur param
//! \param nom, numEpisode, duree
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree)
	:numEpisode_(numEpisode), nom_(nom), duree_(duree)
{
}

//! Opérateur qui compare un int avec le numero episode
//! \param num episode avec le quel on veut comparé l'episode
//! \return vrai si les numeros sont identique, faux sinon
bool Episode::operator==(unsigned int numEpisode)
{
	if (numEpisode == numEpisode_)
		return true;
	return false;
}

//! Opérateur friend qui compare un int avec le numero episode
//! \param num episode avec le quel on veut comparé l'episode
//! \return vrai si les numeros sont identique, faux sinon
bool operator==(unsigned int numEpisode, Episode episode)
{
	return (episode == numEpisode);
}

//! operateur qui affiche un episode
//! \param os Le stream dans lequel afficher
//! \param l'episode a afficher
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
	std::string episode_string;

	if(episode.numEpisode_ < 10)
		episode_string= "Episode 0";
	else
		episode_string = "Episode ";
	
	os << episode_string << episode.numEpisode_ << ": " << episode.nom_ << " | Durée: " << episode.duree_;
	return os;
}

//! Opérateur permet d’initialiser tous les attributs de la classe episode
//! \param episode lequel on veut init ses attributs
//! \return input stream
std::istream& operator>>(std::istream& is, Episode& episode)
{
    is >> episode.numEpisode_ >> std::quoted(episode.nom_) >> std::quoted(episode.duree_);
	return is;
}

//! Getter numEpisode
unsigned int Episode::getNumEpisode() const
{
	return numEpisode_;
}

