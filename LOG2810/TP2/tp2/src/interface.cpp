#include "interface.h"
#include <cstdlib>
#include <ctime>


Interface::Interface() : lexique_(), estInit_(false) {}


// C1 peut creer le lexique et l'automate a partir d'un fichier text
void Interface::creerLexique(std::string filename) {
	
	lexique_ = Lexique(filename);					//*****Path a ajuster!********
	automate_ = Automate(lexique_);
	estInit_ = true;
	
}

// C3 permet de choisir au hasard un secret dans le lexique
void Interface::modeAuto() {
	
	srand((unsigned)time(NULL));
	int randomIndex = rand() % lexique_.getLexique().size();
    motChoisit_ = lexique_.getLexique()[randomIndex];
	
}

// C2 mode Versus lance une methode dans automate.cpp
void Interface::modeVersus() {
    motChoisit_ = automate_.chercherCode();
}



void Interface::auJeu() {
	
    std::cout << "Le mot a ete choisit, AU JEU ! \n";
    std::cout << "Le mot recherche a : " << motChoisit_.size() << " lettres.\n";

	int nbTentative = 0;

    while(!creerVerif(nbTentative)){}
	
	if(nbTentative < 15)
		std::cout << "\n\nHouuurrraaaaaa, vous avez trouve le mot! Felicitation!\n\n\n";
	else
		return;
}

// C2 creer une machine de Mealy qui verifie le mot entrer par le joueur
bool Interface::creerVerif(int& nbTentative) {
	
	std::string monEssaie;
	std::cout << "Il vous reste " << 15 - nbTentative << " essais.\n" << "Entrez un essaie : ";
	std::cin >> monEssaie;
	std::cout << "\n";

	nbTentative++;
	bool grandeurMot = true;
	
	if (monEssaie.size() != motChoisit_.size()) {
		grandeurMot = false;
		std::cout << "La bonne longueur est " << motChoisit_.size() << "\n";
		nbTentative--;
	}
	
	bool inAlphabet = true;
	
	if (grandeurMot) {
		if (!estDansAlphabet(monEssaie)) {
			inAlphabet = false;
			std::cout << "Mauvaises lettres utilise\n";
			nbTentative--;
		}
	}
	
	if (grandeurMot && inAlphabet && monEssaie != motChoisit_)
		std::cout << "Le nombre d'erreurs est : " << nbErreurs(monEssaie) << "\n";
	
	if(monEssaie == motChoisit_ && nbTentative < 15)
		return true;
	
	if(nbTentative == 15) {
		std::cout << "\n\nAhaha loser, vous avez pas trouve.\n\n\n";
		return true;
	}
	
	return false;
}

bool Interface::estDansAlphabet(std::string essaie){
	
	auto alph = lexique_.getAlphabet();
	
	for (char letter : essaie) {
		if (alph.find(letter) == alph.end()) {
			return false;
		}
	}
	
	return true;
}

int Interface::nbErreurs(std::string essaie){
	
	int nombreErreurs = 0;
	
	for(int i = 0; i < motChoisit_.size(); i++){
		if (essaie[i] != motChoisit_[i])
			nombreErreurs++;
	}
	
	return nombreErreurs;
}




void Interface::createInterface() {
	std::cout << "Bienvenu\n";

	char option = 'z';
	while (option != 'e') {
		
		std::cout << "(1)  Initialisation du jeu \n";
		std::cout << "(2)  Partie contre l'ordinateur \n";
		std::cout << "(3)  Deux joueurs \n";
        std::cout << "(4)  Quitter \n";
		std::cout << "Entrer une option: ";
		std::cin >> option;
		std::cout << "\n";

		if (option == '1') {
			
			//initialiser jeu
			std::string fileName;
			std::cout << "Entrer le nom du fichier text: ";
			std::cin >> fileName;
			//create lexique
			creerLexique(fileName);
			
		}
		else if (option == '2')	{
			
			if (estInit_) {
				// partie vs ordi
                modeAuto();
                auJeu();
				
			}else {
				std::cout << "Initialiser le jeux en premier\n\n";
			}
		}
		
		else if (option == '3')	{
			if (estInit_) {
				//parti a deux joueurs
                modeVersus();
                auJeu();
			}
			else {
				std::cout << "Initialiser le jeux en premier\n\n";
			}
		}
		else if (option == '4') {
			exit(0);
		}
	}
	
}
