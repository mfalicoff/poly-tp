#ifndef VEHICULE_H
#define VEHICULE_H

#include <string>

class Vehicule {
	
public:
	Vehicule(std::string type, int max, int coef);

	//getters
	std::string getType() const;
	int getMaxAutonomie() const;
	int getautonomieActuelle() const;
	int getCoefAuto() const;

	//setters
	void setAutonomieActuelle(int nouvelleAut);
	void setcoefAuto(int nouveauCoef);

private:
	std::string type_;
	int maxAutonomie_;
	int autonomieActuelle_;
	int coefAuto_;
};

#endif
