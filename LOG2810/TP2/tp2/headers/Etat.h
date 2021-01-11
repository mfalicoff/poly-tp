#pragma once
#include <vector>
#include <memory>
#include <string>


class Etat {
private:
	std::vector<std::shared_ptr<Etat>> prochainsEtats_;
	bool estBonMot_;
	std::string valeur;

public:
	~Etat() = default;
	Etat();
	Etat(std::string val);
	std::string getValeur();
	std::vector<std::shared_ptr<Etat>>& getProchainsEtats();
	void setBonMot(bool val);
	bool estMot();

};
