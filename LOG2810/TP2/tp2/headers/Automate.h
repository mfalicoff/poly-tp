#pragma once
#include "Etat.h"
#include <memory>
#include <string>
#include <vector>
#include "Lexique.h"
#include <fstream>
#include <unordered_map>

class Lexique;

class Automate {
private:
	std::shared_ptr<Etat> etatActuel_;
	//std::vector<std::shared_ptr<Etat>> etatsInits_;
	std::shared_ptr<Etat> etatInit_;

public:
	Automate() = default;
	Automate(Lexique &lexique);
	std::string chercherCode();
	void trouverEnfant(std::vector<std::shared_ptr<Etat>>& listEnfant, std::shared_ptr<Etat> etat);
	void imprimerSuggestions(const std::vector<std::shared_ptr<Etat>>& listEnfant);
};
