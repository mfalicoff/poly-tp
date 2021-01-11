/* ////////////////////////////////////////////////////////////////
/	TD3 : fichier Serie.cpp                                       /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 1er Mars 2020 � 23h55						  /
/   Description: Implementation de la classe Serie	              /
*//////////////////////////////////////////////////////////////////

#include "Serie.h"

//! Constructeur de la classe Serie
Serie::Serie(Auteur* auteur)
    
    : Media(auteur, TypeMedia::Serie)
    , GestionnaireSaisons()
{
}

//! Constructeur par parametre de la classe Serie
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur)
    
    : Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, TypeMedia::Serie)
    , GestionnaireSaisons()
{
}

//! Constructeur par copie de la classe serie
//! \param la serie que l'on veut copier 
Serie::Serie(const Serie& serie)
    : Media(serie), GestionnaireSaisons()
{
    saisons_.clear();
    for (unsigned int i = 0; i < serie.saisons_.size(); i++)
    {
 		saisons_.push_back(std::make_unique<Saison>(*serie.saisons_[i]));

    }
}

//! methode qui affiche une serie en appelant l'operateur de la saison
//! \param os Le stream dans lequel afficher
std::ostream& Serie::afficher(std::ostream& os) const
{
    
    Media::afficher(os);
    for (int i = 0; i < saisons_.size(); i++)
    {
        os << "\t" << *saisons_[i];
    }
    return os;
}

//! M�thode qui clone la serie retournant un unique_ptr d'une copie de la serie
//! retourne le unique_ptr
std::unique_ptr<Media> Serie::clone() const
{
    
    return std::make_unique<Serie>(*this); 
}