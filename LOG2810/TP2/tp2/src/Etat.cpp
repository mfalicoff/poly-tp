#include "Etat.h"

//Etat() : isLastState = false {}

Etat::Etat() : valeur(""), estBonMot_(false) 
{
	prochainsEtats_ = {};
}

Etat::Etat(std::string val) : valeur(val), prochainsEtats_(), estBonMot_(false) {}


std::string Etat::getValeur() {
    return valeur;
}

std::vector<std::shared_ptr<Etat>>& Etat::getProchainsEtats() {
	return prochainsEtats_;
}

void Etat::setBonMot(bool val) {
	estBonMot_ = val;
}

bool Etat::estMot() {
	return estBonMot_;
}


