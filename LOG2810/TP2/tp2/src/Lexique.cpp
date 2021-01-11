#include "Lexique.h"

Lexique::Lexique(std::string fileName) {
	
	std::ifstream fichier(fileName);

	if(fichier) {
		std::string ligne;

		while(std::getline(fichier, ligne)) {
			if (ligne != " ") {
				lexique_.push_back(ligne);
				for(auto i = 0; i < ligne.size(); i++) {
					if(alphabet_.find(ligne[i]) == alphabet_.end()) {
						alphabet_.emplace(ligne[i], 1);
					}else {
						if (alphabet_.find(ligne[i])->first == ligne[i])
							alphabet_.find(ligne[i])->second++;
					}
				}
			}
		}
	}else {
		throw;
	}
}

std::vector<std::string> Lexique::getLexique(){
	return lexique_;
}

std::unordered_map<char, int> Lexique::getAlphabet()
{
	return alphabet_;
}

