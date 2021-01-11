#include "Automate.h"
#include <iostream>
#include <algorithm>
#include <string>

// Suite du C2 qui permet de get le code a partir des etats dans l'automate
std::string Automate::chercherCode() {
	bool trouve = false;
	std::string code;
	std::string codeFinal;
	
	while(!trouve) {
		
		//Demander le code
		std::cout << ">Quel code?\n";
		std::cout << "Reponse: ";
		std::cin >> code;
		
		std::shared_ptr<Etat> etatCourant = etatInit_;

		//Parcourir tous les état jusqu'à un problème ou un mot trouvé
		for(int i=1; i<=code.length(); i++) {
			
			auto listeProchainEtats = (etatCourant)->getProchainsEtats();

			auto test = std::string(&code[0], i);

			auto it = std::find_if(listeProchainEtats.begin(), listeProchainEtats.end(), [&code, i](std::shared_ptr<Etat>& etat)
				{return etat->getValeur() == std::string(&code[0], i); });

			if(it == listeProchainEtats.end()) {
				std::cout << "Ce mot n'existe pas dans le lexique\n";
				break;
			}
			
			etatCourant = *it;
		}

		if ((etatCourant)->estMot()) {

			std::string rep;
			std::cout << "Voulez-vous selectionner ce code ? (1:oui / 0:non)\n";
			std::cout << "Reponse: ", std::cin >> rep;
			if(rep == "1") {
				codeFinal = (etatCourant)->getValeur();
				trouve = true;
			}
		}
		else {
			
			std::vector<std::shared_ptr<Etat>> listEnfant;
			trouverEnfant(listEnfant, etatCourant);
			imprimerSuggestions(listEnfant);
		}
	}
	return codeFinal;
}


void Automate::trouverEnfant(std::vector<std::shared_ptr<Etat>>& listEnfant, std::shared_ptr<Etat> etat) {
	
	if (etat->estMot())	{
		listEnfant.push_back(etat);
	}
	
	for (std::shared_ptr<Etat> etatProchain : etat->getProchainsEtats()) {
		trouverEnfant(listEnfant, etatProchain);
	}
}

void Automate::imprimerSuggestions(const std::vector<std::shared_ptr<Etat>>& listEnfant) {
	
	std::cout << "Suggestion(s)\n";
	
	for (std::shared_ptr<Etat> enfant : listEnfant)	{
		std::cout << enfant->getValeur() << "\n";
	}
}

Automate::Automate(Lexique& lexique){

	etatInit_ = std::make_shared<Etat>();
	auto lex = lexique.getLexique();


	for (int i = 0; i < lex.size(); i++) {
		//auto currentStateBranch = &etatsInits_;
		auto currentStateBranch = &etatInit_->getProchainsEtats();
		
		auto word = lex[i];
		std::string currentStateWord;
		
		for (int j = 0; j < word.size(); j++) {

			auto letter = word[j];
			int b = 3;
			currentStateWord.push_back(letter);
			auto it = std::find_if(currentStateBranch->begin(), currentStateBranch->end(), [&currentStateWord](std::shared_ptr<Etat>& etat) {
				auto wordOfEtat = etat->getValeur();
				return wordOfEtat == currentStateWord;
				});
			int c = 3;
			if (it == currentStateBranch->end()) {
				Etat nvEtat(currentStateWord);
				if (letter == word[word.size() - 1] && j == word.size()-1) {
					nvEtat.setBonMot(true);
				}
				auto newEtat = std::make_shared<Etat>(nvEtat);
				currentStateBranch->push_back(newEtat);
				currentStateBranch = &currentStateBranch->at(currentStateBranch->size() - 1)->getProchainsEtats();
			} else {
				currentStateBranch = &(*it)->getProchainsEtats();
			}
		}
	}
}


