#pragma once
#include <iostream>
#include <string>
#include "Automate.h"
#include "Lexique.h"

class Interface {
private:
	std::string motChoisit_;
	Automate automate_;
	Lexique lexique_;
	bool estInit_;
public:
	Interface();
	void creerLexique(std::string filename);
	void createInterface();
    void modeAuto();
    void modeVersus();
    void auJeu();
	bool creerVerif(int& nbTentative);
	int nbErreurs(std::string essaie);
    bool estDansAlphabet(std::string essaie);
};