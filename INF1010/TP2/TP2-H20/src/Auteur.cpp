
/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier Film.cpp                                        /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 11 fevrier 2020 � 23h55                      /
/   Description: Implementation de la classe Auteur               /
*//////////////////////////////////////////////////////////////////
#include "Auteur.h"
#include <iostream>

//! Constructeur de la classe Auteur
//! \param nom              Nom de l'auteur
//! \param anneeDeNaissance Ann�e de naissance de l'auteur
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance)
    : nom_(nom)
    , anneeDeNaissance_(anneeDeNaissance)
    , nbFilms_(0)
{}

//! M�thode qui affiche un auteur par surcharge d operateur <<
//! \param stream Le stream dans lequel afficher et l auteur qui est affiche
std::ostream& operator<<(std::ostream& stream, const Auteur& auteur)
{
    // Ne modifiez pas cette fonction
    stream << "Nom: " << auteur.getNom() << " | Date de naissance: " << auteur.getAnneeDeNaissance()
        << " | Nombre de films: " << auteur.getNbFilms();
    return stream;
}

//! M�thode qui compare un auteur avec un string
//! \param le nom de l auteur string qui doit etre compare
// return un booleen
bool Auteur::operator==(std::string nom)
{
    if (nom_ == nom)
        return true;
    else
        return false;
}
//! M�thode qui compare un auteur avec un string
//! \param le nom de l auteur string qui doit etre compare avec le nom de l auteur passe en parametre 
// return un booleen
bool operator==(std::string nom, Auteur auteur)
{
    return (auteur == nom);
}
//! M�thode qui retourne le nom de l'auteur
//! \return Le nom de l'auteur
const std::string& Auteur::getNom() const
{
    return nom_;
}

//! M�thode qui retourne l'ann�e de naissance de l'auteur
//! \return L'ann�e de naissance de l'auteur
unsigned int Auteur::getAnneeDeNaissance() const
{
    return anneeDeNaissance_;
}

//! M�thode qui retourne le nombre de films de l'auteur
//! \return Le nombre de films de l'auteur
unsigned int Auteur::getNbFilms() const
{
    return nbFilms_;
}

//! M�thode qui set le nombre de films de l'auteur
//! \param nbFilms  Le nombre de films de l'auteur
void Auteur::setNbFilms(unsigned int nbFilms)
{
    nbFilms_ = nbFilms;
}