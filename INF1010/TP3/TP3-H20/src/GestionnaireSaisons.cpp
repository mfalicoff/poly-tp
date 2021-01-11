/* ////////////////////////////////////////////////////////////////
/	TD3 : fichier GestionnaireSaisons.cpp                         /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano Falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 1er Mars 2020 � 23h55						  /
/   Description: Implementation de la classe GestionnaireSaisons  /
*//////////////////////////////////////////////////////////////////

#include "GestionnaireSaisons.h"

//! Destructeur de la classe GestionnaireSaisons
GestionnaireSaisons::~GestionnaireSaisons()
{
	saisons_.clear();
}

//! opérateur qui ajoute une saison au vectuer de saisons
//! \param auteur La saison à ajouter
GestionnaireSaisons& GestionnaireSaisons::operator+=(std::unique_ptr<Saison> saison)
{
	if (trouverIndexSaison(saison->getNumSaison()) == SAISON_INEXSISTANTE)
	{
		saisons_.push_back(std::move(saison));
	}
	else
	{
		saisons_[trouverIndexSaison(saison->getNumSaison())] = std::move(saisons_[saisons_.size()-1]);
	}
	sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());
	return *this;
}

//! opérateur qui suprime une saison
//! \param auteur Le numero de la saison a supprimer
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
	int indexSaison = trouverIndexSaison(numSaison);
    if (indexSaison != SAISON_INEXSISTANTE)
    {
        saisons_[indexSaison] = std::move(saisons_[saisons_.size() - 1]);
        saisons_.pop_back();
    }
	sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());

    return *this;
	
}

//! methode qui ajoute un episode à la saison
//! \param L'episode à ajouter
//! \utilise l'operateur += de la classe saison
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison, std::unique_ptr<Episode> episode)
{
	if(trouverIndexSaison(numSaison) != -1)
	{
		*(saisons_[trouverIndexSaison(numSaison)]) += std::move(episode);
	}
}

//! methode qui retire un episode à la saison
//! \param le numero de L'episode à ajouter, et le numero de la saiosn a lequel il appartient
//! \utilise l'operateur -= de la classe saison
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
    if(trouverIndexSaison(numSaison) != -1)
	{
		*(saisons_[trouverIndexSaison(numSaison)]) -= numEpisode;
	}
}

//! Méhode qui cherche une saison par son numero de saison
//! \param numero de Saison
//! \return l'index de la saison dans le vecteur des saisons
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
	for (int i = 0; i < saisons_.size(); i++)
	{
		if (saisons_[i]->getNumSaison() == numSaison)
			return i;
	}

	return -1;
}

//! Méhode qui cherche une saison par son numero de saison
//! \param numero de Saison
//! \return un pointeur vers le smart_ptr de la saison
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
	if (trouverIndexSaison(numSaison) == -1)
		return nullptr;
	return saisons_[trouverIndexSaison(numSaison)].get();
}

//! Méhode qui get le nb saison d'une serie
size_t GestionnaireSaisons::getNbSaisons() const
{
	return saisons_.size();
}
