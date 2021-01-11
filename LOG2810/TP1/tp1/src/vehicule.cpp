#include "vehicule.h"


Vehicule::Vehicule(std::string type, int max, int coef) : type_(type), maxAutonomie_(max), coefAuto_(coef) { autonomieActuelle_ = max; }


//getters and setters
void Vehicule::setAutonomieActuelle(int nouvelleAut) {
	autonomieActuelle_ = nouvelleAut;
}

void Vehicule::setcoefAuto(int nouveauCoef) {
	coefAuto_ = nouveauCoef;
}

int Vehicule::getMaxAutonomie() const {
	return maxAutonomie_;
}

std::string Vehicule::getType() const {
	return type_;
}

int Vehicule::getautonomieActuelle() const {
	return autonomieActuelle_;
}

int Vehicule::getCoefAuto() const {
	return coefAuto_;
}
