/* ////////////////////////////////////////////////////////////////
/	TD3 : fichier Media.cpp										  /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano Falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 1er Mars 2020 � 23h55						  /
/   Description: Implementation de la classe Media				  /
*//////////////////////////////////////////////////////////////////

#include "Media.h"

namespace
{
    //! Fonction qui convertit le enum Media::Genre en string
    //! \param genre    Le genre à convertir
    //! \return         Le string qui représente le enum
    const std::string& getGenreString(Media::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Media::Genre>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string
    //! \param pays     Le pays à convertir
    //! \return         Le string qui représente le enum
    const std::string& getPaysString(Pays pays)
    {
        static const std::string NOMS_PAYS[] = {"Bresil",
                                                "Canada",
                                                "Chine",
                                                "EtatsUnis",
                                                "France",
                                                "Japon",
                                                "RoyaumeUni",
                                                "Russie",
                                                "Mexique"};
        auto index = enum_value(pays);
        assert(valid_as_enum<Pays>(index));
        return NOMS_PAYS[index];
    }
} // namespace

//! Constructeur de la classe Media
Media::Media(Auteur* auteur, Media::TypeMedia typeMedia)
	:auteur_(auteur), typeMedia_(typeMedia), nom_(""), anneeDeSortie_(0), genre_(Genre()), pays_(Pays()), estRestreintParAge_(0)
{
}

//! Constructeur de la classe Media par parametre
Media::Media(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur, Media::TypeMedia typeMedia)
	:nom_(nom), anneeDeSortie_(anneeDeSortie), genre_(genre), pays_(pays), estRestreintParAge_(estRestreintParAge),	auteur_(auteur), typeMedia_(typeMedia), paysRestreints_(0)
{
}

//! Constructeur par copie de la classe Media
//! \param Media              
Media::Media(const Media& media)
{
	paysRestreints_.clear();
	for (unsigned int i = 0; i < media.paysRestreints_.size(); i++)
    {
        paysRestreints_.push_back(media.paysRestreints_[i]);
    }
	nom_ = media.nom_;
	anneeDeSortie_ = media.anneeDeSortie_;
	genre_ = media.genre_;
	pays_ = media.pays_;
	estRestreintParAge_ = media.estRestreintParAge_;
	auteur_ = media.auteur_;
	typeMedia_ = media.typeMedia_;
}

//! Destructeur de la classe Media
Media::~Media()
{
	paysRestreints_.clear();
}

//! Méhode qui get un auteur d'un Media
Auteur* Media::getAuteur() const 
{
	return auteur_;
}

//! methode qui ajoute un pays restreint au vecteur des pays restreints
//! \param le pays a ajouter
void Media::ajouterPaysRestreint(Pays pays)
{
	paysRestreints_.push_back(pays);
}

//! methode qui supprime les pays restreints
void Media::supprimerPaysRestreints()
{
	paysRestreints_.clear();
}

//! methode cherche si un pays est restreint du media
//! \param le pays a chercher
//! \return un bool si le pays appartient a la liste
bool Media::estRestreintDansPays(Pays pays) const
{
	for (std::size_t i = 0; i < paysRestreints_.size(); i++)
	{
		if (paysRestreints_[i] == pays)
		{
			return true;
		}
	}
	return false;
}

//! methode return si le media est restraint par age
bool Media::estRestreintParAge() const
{
	return estRestreintParAge_;
}

//! methode qui affiche un media
//! \param os Le stream dans lequel afficher
std::ostream& Media::afficher(std::ostream& os) const
{
	os << nom_ << "\n\tDate de sortie: " << anneeDeSortie_
		<< "\n\tGenre: " << getGenreString(genre_) << "\n\tAuteur: " << auteur_->getNom()
		<< "\n\tPays: " << getPaysString(pays_)
		<< (paysRestreints_.size() == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

	for (std::size_t i = 0; i < paysRestreints_.size(); i++)
	{
		os << "\n\t\t" << getPaysString(paysRestreints_[i]);
	}
	os << '\n';
	return os;
}

//! operateur qui appelle afficherMedia 
//! \param os Le stream dans lequel afficher
//! \param Media lequel afficher
std::ostream& operator<<(std::ostream& os, const Media& media)
{
	media.afficher(os);
	return os;
}

//GETTERS
Media::Genre Media::getGenre() const
{
	return genre_;
}

const std::string& Media::getNom() const
{
	return nom_;
}


Media::TypeMedia Media::getTypeMedia() const
{
	return typeMedia_;
}

//! Methode permet d’initialiser tous les attributs de la classe Media
//! \return input stream
std::istream& Media::lire(std::istream& is)
{
	int genreValeurEnum;
    int paysValeurEnum;

    is >> std::quoted(nom_) >> anneeDeSortie_ >> genreValeurEnum >> paysValeurEnum >> estRestreintParAge_;
    genre_ = to_enum<Media::Genre>(genreValeurEnum);
    pays_ = to_enum<Pays>(paysValeurEnum);

    return is;
}

//! Opérateur permet d’initialiser tous les attributs de la classe Media en appelant a methode lire
//! \param Media lequel on veut init ses attributs
//! \return input stream
std::istream& operator>>(std::istream& is, Media& media)
{
	media.lire(is);
	return is;
}

//! M�thode qui clone un media retournant un unique_ptr d'une copie du media
//! retourne le unique_ptr
std::unique_ptr<Media> Media::clone() const
{
	auto media_act = std::make_unique<Media>(*this);
    return std::move(media_act);
}