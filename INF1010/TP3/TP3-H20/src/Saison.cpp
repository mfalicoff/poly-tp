/* ////////////////////////////////////////////////////////////////
/	TD3 : fichier Saison.cpp                                      /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 1er Mars 2020 � 23h55						  /
/   Description: Implementation de la classe Saison	              /
*//////////////////////////////////////////////////////////////////

#include "Saison.h"

//! Constructeur de la classe Saison
Saison::Saison()
	:numSaison_(0), nbEpisodesmax_(0)
{
}

//! Constructeur par parametre de la classe Saison
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax)
    :numSaison_(numSaison), nbEpisodesmax_(nbEpisodemax)
{
}

//! Constructeur par copie de la classe Saison
//! \param la saison que l'on veut copier 
Saison::Saison(const Saison& saison)
{
	episodes_.clear();
	numSaison_ = saison.numSaison_;
	nbEpisodesmax_ = saison.nbEpisodesmax_;
	
	for (int i = 0; i < saison.getNbEpisodes(); i++)
	{
		episodes_.push_back(std::make_unique<Episode>(*saison.episodes_[i]));
	}
}

//! Destructeur de la classe Media
Saison::~Saison()
{
	episodes_.clear();
}

//! opérateur qui ajoute un episode a la saion
//! \param l'episode a ajouter
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
	    
    int indexEpisode = trouverIndexEpisode(episode->getNumEpisode());
    if (indexEpisode != EPISODE_INEXSISTANTE)
    {
        episodes_[indexEpisode] = std::move(episodes_[episodes_.size() - 1]);
        episodes_.pop_back();
    }
    episodes_.push_back(std::move(episode));
    sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
    return *this;
}

//! opérateur qui retire un episode a la saion
//! \param auteur le numero de l'episode a supprimer
Saison& Saison::operator-=(unsigned int numEpisode)
{
	    
    int indexEpisode = trouverIndexEpisode(numEpisode);
    if (indexEpisode != EPISODE_INEXSISTANTE)
    {
        episodes_[indexEpisode] = std::move(episodes_[episodes_.size() - 1]);
        episodes_.pop_back();
    }
    sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
    return *this;
}

//! opérateur qui test l'egalite entre une saison et un int
//! \param le numero de saison a comparer
bool Saison::operator==(unsigned int numSaison)
{
	if (numSaison == numSaison_)
		return true;
	return false;
}

bool operator==(unsigned int numSaison, const Saison& saison)
{
	return (numSaison == saison);
}

//! methode qui affiche une saison
//! \param os Le stream dans lequel afficher
//! \param saison a afficher
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
	std::string etatSaison;
    std::string saison_str;
    if (saison.episodes_.size() == saison.nbEpisodesmax_)
    {
        etatSaison = "(Terminée)";
    }
    else
    {
        etatSaison = "(En cours)";
    }
    if (saison.numSaison_ < 10)
    {
        saison_str = "Saison0";
    }
    else
    {
        saison_str = "Saison";
    }
    os << saison_str << saison.numSaison_ << ": " << saison.episodes_.size() << "/"
       << saison.nbEpisodesmax_ << etatSaison << std::endl;
    for (int i = 0; i < saison.episodes_.size(); i++)
    {
        os << "\t\t" << *(saison.episodes_[i]) << std::endl;
    }

    return os;
}

//! Opérateur permet d’initialiser tous les attributs de la classe saison
//! \param Media lequel on veut init ses attributs
//! \return input stream
std::istream& operator>>(std::istream& is, Saison& saison)
{
	is >> saison.numSaison_ >> saison.nbEpisodesmax_;
	return is;
}

//GETTERS
unsigned int Saison::getNumSaison() const
{
	return numSaison_;
}

size_t Saison::getNbEpisodes() const
{
	return episodes_.size();
}

size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
	for (int i = 0; i < episodes_.size(); i++)
	{
		if (*episodes_[i] == numEpisode)
			return i;

	}
	return -1;
}