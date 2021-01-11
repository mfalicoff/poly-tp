// TODO: Faire l'entête de fichier

/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier GestionnaireAuteurs.cpp                         /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 28 janvier 2020 à 23h55                      /
/   Description: Implementation de la classe GestionnaireAuteurs  /
*//////////////////////////////////////////////////////////////////
#include "GestionnaireAuteurs.h"

// TODO: Inclure la définition de la classe appropriée
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// TODO fait: Constructeur par défault en utilisant la liste d'initialisation
GestionnaireAuteurs::GestionnaireAuteurs(): nbAuteurs_ (0){}

// TODO fait: ajouterAuteur(const Auteur& auteur)
//! Méthode qui ajoute un auteur dans la liste des auteurs.
//! \param auteur Auteur à ajouter à la liste.
bool GestionnaireAuteurs::ajouterAuteur(const Auteur& auteur) {
	
	if (nbAuteurs_ < NB_AUTEURS_MAX)
	{
		auteurs_[nbAuteurs_] = auteur;
		nbAuteurs_++;
		return true;
	}
	else return false;
}


// TODO fait: chercherAuteur(const std::string& nomAuteur)
//! Méthode qui cherche un auteur dans la liste des auteurs.
//! \param nom de l'auteur à chercher dans la liste
Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur) {
	
	for (size_t i = 0; i < nbAuteurs_; i++) {
		if (auteurs_[i].getNom() == nomAuteur)
			return &auteurs_[i];
		
	}

	return nullptr;
}

//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs.
//! \param nomFichier   Le nom du fichier à charger.
//! \return             Un bool représentant si le chargement a été un succès.
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier) {
	std::ifstream fichier(nomFichier);
	if (fichier) {
		// TODO: envoyer chaque ligne à lireLigneAuteur
		std::string ligne;
		
		nbAuteurs_ = 0;

		while (std::getline(fichier, ligne)) {

			if (!lireLigneAuteur(ligne))       // Le compilateur effectue " lireligne" et verifie si ce n'est pas le cas
				return false;                 

			
		}
		return true;
	}
	else {

		std::cerr << "Le fichier " << nomFichier
			<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
		return false;
	}

	return false;
}

//! Méthode qui affiche la liste des auteurs.
//! \param stream Le stream dans lequel afficher.
void GestionnaireAuteurs::afficher(std::ostream& stream) const {
	// Ne pas modifier cette méthode
	for (std::size_t i = 0; i < nbAuteurs_; i++) {
		auteurs_[i].afficher(stream);
		stream << '\n';
	}
}

// TODO getNbAuteurs() const: Retourner le nombre d'auteurs dans la liste
std::size_t GestionnaireAuteurs::getNbAuteurs() const { return nbAuteurs_; }

//! Méthode qui ajoute un auteur avec un string.
//! \param ligne Le string qui comporte tous les attributs de l'auteur.
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne) {
	std::istringstream stream(ligne);
	std::string nom;
	unsigned int age;
	stream >> std::quoted(nom)>> age;   // lire en premier nom ensuite age ( std :: quoted pour lire les carac entre guillemets
	Auteur test(nom, age);
	return(ajouterAuteur(test));
}