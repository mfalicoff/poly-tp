/* ////////////////////////////////////////////////////////////////
/	TD3 : fichier Film.cpp                                        /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 1er Mars 2020 � 23h55						  /
/   Description: Implementation de la classe Film	              /
*//////////////////////////////////////////////////////////////////

#include "Film.h"


//! Constructeur de la classe Film
//! \param Auteur              Auteur
//! \Apelle le constructeur de la classe Media avec l'auteur en param
Film::Film(Auteur* auteur)
	:Media(auteur, Media::TypeMedia::Film), duree_("")
{
}

//! Constructeur de la classe Film
//! \param nom, anneeDeSortie, genre, pays, estRestreintparAge,Auteur, duree
//! \Apelle le constructeur de la classe Media avec les param de Media
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur, const std::string& duree)
	:Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia::Film),
	duree_(duree)
{
}

//! M�thode qui affiche le film en appelant afficher Media
//! \param stream Le stream dans lequel afficher
//! retourne le stream
std::ostream& Film::afficher(std::ostream& os) const
{
	Media::afficher(os);
	os << "\tDurée: " << duree_;
	return os;
}

//! M�thode qui lis le film en appelant lire Media
//! \param stream Le stream dans lequel afficher
//! retourne le stream
std::istream& Film::lire(std::istream& is)
{
    Media::lire(is) >> std::quoted(duree_);
	return is;
}

//! M�thode qui clone le film retournant un unique_ptr d'une copie du film
//! retourne le unique_ptr
std::unique_ptr<Media> Film::clone() const
{
	return std::make_unique<Film>(*this);
}
