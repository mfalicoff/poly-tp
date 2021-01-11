
#ifndef AUTEUR_H
#define AUTEUR_H

#include <string>

class Auteur
{
public:
	Auteur() = default;                            
	Auteur(const std::string& nom, unsigned int anneeDeNaissance);
	const std::string& getNom() const;
	unsigned int getAnneeDeNaissance() const;
	unsigned int getNbFilms() const;

	void setNbFilms(unsigned int nbFilms);
	friend std::ostream& operator<< (std::ostream& stream, const Auteur& Auteur);                         // surcharge de l operateur <<
	bool operator== (std::string nom);                                                                    // surcharge de l operateur ==
	friend bool operator==(std::string nom, const  Auteur auteur);                                       // surcharge de l operateur == qui prend comme parametre un auteur 
private:
	std::string nom_;
	unsigned int anneeDeNaissance_;
	unsigned int nbFilms_;
};

#endif // AUTEUR_H

