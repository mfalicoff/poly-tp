/* ////////////////////////////////////////////////////////////////
/	TD3 : fichier Librairie.cpp                                   /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 1er Mars 2020 � 23h55						  /
/   Description: Implementation de la classe Librairie	          /
*//////////////////////////////////////////////////////////////////

#include "Librairie.h"

//! Constructeur par copie de la classe Librairie
//! \param Librairie              
//! \Apelle le clone de la classe Media pour copier touts les medias
Librairie::Librairie(const Librairie& librairie)
{
    medias_.clear();
    for (unsigned int i = 0; i < librairie.medias_.size(); i++)
    {
        medias_.push_back(((librairie.medias_[i])->clone()));
    }
}

//! operateur qui surcharge l'operatuer =
//! \param Librairie lequelle on veut copier
//! \param out: la nouvelle librairie avec les nouveaux attributs
Librairie& Librairie::operator=(const Librairie& librairie)
{
    if (&librairie == this)
        return *this;

    medias_.clear();

    for (unsigned int i = 0; i < librairie.medias_.size(); i++)
    {
        for (unsigned int i = 0; i < librairie.medias_.size(); i++)
	    {
			medias_.push_back(((librairie.medias_[i])->clone()));
	    }
    }

    return *this;
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    medias_.clear();
}

//! Methode qui cherche un film
//! \param in: nomFilm
//! \param out: un pointeur au film recherche
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
	if (chercherMedia(nomFilm, Media::TypeMedia::Film) == nullptr) return nullptr;
	return dynamic_cast<Film*>(chercherMedia(nomFilm, Media::TypeMedia::Film));
}

//! Methode qui cherche une serie
//! \param in: nomSerie
//! \param out: un pointeur a la serie recherche
Serie* Librairie::chercherSerie(const std::string& nomSerie)
{
    if(chercherMedia(nomSerie, Media::TypeMedia::Serie) == nullptr) return nullptr;
	return dynamic_cast<Serie*>(chercherMedia(nomSerie, Media::TypeMedia::Serie));
}

//! Methode qui ajoute une saison
//! \param in: nomSerie et un pointeur a la saison a ajouter
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
    int indexMedia = trouverIndexMedia(nomSerie);
    if (indexMedia != MEDIA_INEXSISTANT)
    {
        if (medias_[indexMedia]->Media::getTypeMedia() == Media::TypeMedia::Serie)
        {
            dynamic_cast<Serie*>((medias_[indexMedia]).get())->GestionnaireSaisons::operator+=(std::move(saison));
        }
    }
}

//! Methode qui retire une saison
//! \param in: nomSerie et le numero de saison a retirer
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
    int indexMedia = trouverIndexMedia(nomSerie);
    if (indexMedia != MEDIA_INEXSISTANT)
    {
        if (medias_[indexMedia]->Media::getTypeMedia() == Media::TypeMedia::Serie)
        {
            dynamic_cast<Serie*>((medias_[indexMedia]).get())->GestionnaireSaisons::operator-=(numSaison);
        }
    }
}

//! Methode qui ajoute un episode
//! \param in: nomSerie et un pointeur a l'episode a ajouter et le numero de la saison
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,std::unique_ptr<Episode> episode)
{
    int indexMedia = trouverIndexMedia(nomSerie);
    if (indexMedia != MEDIA_INEXSISTANT)
    {
        if (medias_[indexMedia]->Media::getTypeMedia() == Media::TypeMedia::Serie)
        {
            dynamic_cast<Serie*>((medias_[indexMedia]).get())->GestionnaireSaisons::ajouterEpisode(numSaison, std::move(episode));
        }
    }
}

//! Methode qui ajoute un episode
//! \param in: nomSerie et un pointeur a l'episode a ajouter et le numero de la saison
void Librairie::retirerEpisode(const std::string& nomSerie, unsigned int numSaison, unsigned int numEpisode)
{
    int indexMedia = trouverIndexMedia(nomSerie);
    if (indexMedia != MEDIA_INEXSISTANT)
    {
        if (medias_[indexMedia]->Media::getTypeMedia() == Media::TypeMedia::Serie)
        {
            dynamic_cast<Serie*>((medias_[indexMedia]).get())->GestionnaireSaisons::retirerEpisode(numSaison, numEpisode);
        }
    }
}

//! Méthode qui charge les series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un serie à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerMediasDepuisFichier(const std::string& nomFichier, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // Supprimer les vieux films avant de lire les nouveaux
		for (size_t i = 0; i < medias_.size(); i++)
		{
			Auteur* ok = medias_[i]->getAuteur();
			ok->setNbMedias(ok->getNbMedias() - 1);
		}
		
        medias_.clear();
		
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneMedia(ligne, gestionnaireAuteurs) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui charge les restrictions des series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (size_t i = 0; i < medias_.size(); i++)
            medias_[i]->supprimerPaysRestreints();

        std::string ligne;
        while (getline(fichier, ligne))
            if (!lireLigneRestrictions(ligne))
                return false;

        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! operateur qui affiche toute la librairie
//! \param os Le stream dans lequel afficher et la librairie
//! \param le ostream
std::ostream& operator<<(std::ostream& os, const Librairie& librairie)
{
    
    for (std::size_t i = 0; i < librairie.medias_.size(); i++)
    {
        if(librairie.medias_[i]->getTypeMedia() == Media::TypeMedia::Film)
			os << *(librairie.medias_[i]) << std::endl;
    }

	 for (std::size_t i = 0; i < librairie.medias_.size(); i++)
    {
        if(librairie.medias_[i]->getTypeMedia() == Media::TypeMedia::Serie)
			os << *(librairie.medias_[i]) << std::endl;
    }


    return os;
}

//! Methode qui toruve l'index du media recerche dans le vecteur medias_
//! \param nomMedia
//! \param index du media
int Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
 	for (int i = 0; i < medias_.size(); i++)
	{
		if (nomMedia == (medias_[i]->getNom()))
			return i;
	}
	return MEDIA_INEXSISTANT;
}

//! opérateur qui ajoute un media a la librairie
//! \param auteur media a ajouter
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{
    if (media == nullptr)
    {
        return *this;
    }
    medias_.push_back(std::move(media));
    return *this;
}

//! opérateur qui enleve un media
//! \param nomMedia
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
    int indexMedia = trouverIndexMedia(nomMedia);
    if (indexMedia == MEDIA_INEXSISTANT)
    {
        return *this;
    }

    medias_[indexMedia] = std::move(medias_[medias_.size() - 1]);
    medias_.pop_back();
    return *this;
}

//! Methode qui cherche un media
//! \param nomMedia, typeMedia
//! \param pointeur vers le smartptr du media
Media* Librairie::chercherMedia(const std::string& nomMedia, Media::TypeMedia typeMedia)
{
    int indexMedia = trouverIndexMedia(nomMedia);
    if ((indexMedia == MEDIA_INEXSISTANT) || (medias_[indexMedia]->getTypeMedia() != typeMedia))
    {
        return nullptr;
    }
    return medias_[indexMedia].get();
}

//! M�thode qui charge les restrictions des medias � partir d'un fichier.
//! \param nomFichier           Le nom du fichier � lire.
//! \return                     Un bool repr�sentant si le chargement a �t� un succ�s.
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomMedia;
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    int mediaValeurEnum;
    stream >> mediaValeurEnum;
    if (stream >> std::quoted(nomMedia))
    {
        Media* media = chercherMedia(nomMedia, to_enum<Media::TypeMedia>(mediaValeurEnum));

        if (media == nullptr)
        {
            // Media n'existe pas
            return false;
        }

        int paysValeurEnum;
        while (stream >> paysValeurEnum)
        {
            media->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
        }
        return true;
    }
    return false;
}

bool Librairie::lireLigneMedia(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    lireLigneMediaFunction fonctionLireligne[] = {&Librairie::lireLigneFilm,
                                                  &Librairie::lireLigneSerie,
                                                  &Librairie::lireLigneSaison,
                                                  &Librairie::lireLigneEpisode};
    std::istringstream stream(ligne);
    int typeMediaValeurEnum;

    if (stream >> typeMediaValeurEnum)
        return invoke(fonctionLireligne[typeMediaValeurEnum], *this, stream, gestionnaireAuteurs);

    return false;
}

//! Méhode qui get les medias
//! \return vecteurs de smart_ptr de medias
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
    return medias_;
}

//! Méthode qui ajoute un episode en appelant la methode approprie de la classe derive
//! \param istream              Le input stream
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un media à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès
bool Librairie::lireLigneEpisode(std::istream& is, GestionnaireAuteurs&)
{
    Episode episode;
    std::string nomSerie;
    int numSaison;
    if (is >> episode >> std::quoted(nomSerie) >> numSaison)
    {
        ajouterEpisode(nomSerie, numSaison, std::make_unique<Episode>(episode));
        return true;
    }
    return false;
}

//! Méthode qui ajoute une serie en appelant la methode approprie de la classe derive
//! \param istream              Le input stream
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un media à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès
bool Librairie::lireLigneSaison(std::istream& is, GestionnaireAuteurs&)
{
    Saison saison;
    std::string nomSerie;
    if (is >> saison >> std::quoted(nomSerie))
    {
        ajouterSaison(nomSerie, std::make_unique<Saison>(saison));
        return true;
    }
    return false;
}

//! Méthode qui ajoute une serie en appelant la methode approprie de la classe derive
//! \param istream              Le input stream
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un media à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès
bool Librairie::lireLigneSerie(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::string nomAuteur;
    if (is >> std::quoted(nomAuteur))
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        Serie serie = Serie(auteur);
        if (is >> serie)
        {
            auteur->setNbMedias(auteur->getNbMedias() + 1);
            *this += std::make_unique<Serie>(serie);
            return true;
        }
        return false;
    }
    return false;
}

//! Méthode qui ajoute un film en appelant la methode approprie de la classe derive
//! \param istream              Le input stream
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un media à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès
bool Librairie::lireLigneFilm(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::string nomAuteur;
    if (is >> std::quoted(nomAuteur))
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        Film film = Film(auteur);
		
        if (is >> film)
        {
            
            *this += std::make_unique<Film>(film);
			auteur->setNbMedias((auteur->getNbMedias()) + 1);
            return true;
        }
        return false;
    }
    return false;
}

//! Méhode qui get le nb films dans le vecteur media
size_t Librairie::getNbFilms() const
{
    size_t cpt_films;
    cpt_films = 0;
    for (size_t i = 0; i < medias_.size(); i++)
    {
        if (medias_[i]->getTypeMedia() == Media::TypeMedia::Film)
        {
            cpt_films += 1;
        }
    }
    return cpt_films;
}

//! Méhode qui get le nb series dans le vecteur media
size_t Librairie::getNbSeries() const
{
    size_t cpt_series;
    cpt_series = 0;
    for (size_t i = 0; i < medias_.size(); i++)
    {
        if (medias_[i]->getTypeMedia() == Media::TypeMedia::Serie)
        {
            cpt_series += 1;
        }
    }
    return cpt_series;
}

//! Méhode qui get le nb saisons d'une serie dans le vecteur media
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
	Librairie lib(*this);
	return (lib.chercherSerie(nomSerie))->getNbSaisons();
}

//! Méhode qui get le nb episodes dans une serie dans une saison dans le vecteur media
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
	Librairie librairie01 = Librairie(*this);
	return librairie01.chercherSerie(nomSerie)->getSaison(numSaison)->getNbEpisodes();
}

//! Méhode qui get le nb medias dans le vecteur media
size_t Librairie::getNbMedias() const
{
	return medias_.size();
}


