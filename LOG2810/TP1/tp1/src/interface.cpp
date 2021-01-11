
#include "interface.h"
#include <iostream>
#include <string>



Interface::Interface() 
{
	vehicule_ = nullptr;
}

void Interface::menu()
{
	char option = 'z';
	while (option != 'e')
	{
		std::cout << "(a)  Demander les caracteristiques du vehicule \n";
		std::cout << "(b)  Mettre a jour la carte \n";
		std::cout << "(c)  Extraire un sous-graphe \n";
		std::cout << "(d)  Determiner le plus court chemin \n";
		std::cout << "(e)  Quitter \n";
		std::cout << "Rentrez l'option voulue:  ";
		std::cin >> option;
		if (option == 'a')
		{
			std::string type = "";
			int autonomieMax = 0;
			int coefAuto = 0;
			std::cout << "Rentrer le type de carburant du vehicule (essence, electric, hybride):  ";
			std::cin >> type;
			std::cout << "Rentrer l'autonomie maximale:  ";
			std::cin >> autonomieMax;
			std::cout << "Rentrer coef d'autonomie:  ";
			std::cin >> coefAuto;
			Vehicule nvVehicule = Vehicule(type, autonomieMax, coefAuto);
			vehicule_ = std::make_unique<Vehicule>(nvVehicule);
			std::cout << '\n';
		}
		else if (option == 'b')
		{
			graphe_.reset();
			std::string inputFileName;
			std::cout << "Rentrez le nom du fichier: ";
			std::cin >> inputFileName;
			graphe_.creerGraphe(inputFileName);
			graphe_.lireGraphe();
			std::cout << '\n';
		}
		else if (option == 'c')
		{
			std::string sommetInit;
			std::cout << "Entrez Sommet partant en lettre majuscule:  ", std::cin >> sommetInit;
			
			if (vehicule_ != nullptr)
			{	
				auto plusLongTrajet = graphe_.extractionGraphe(sommetInit, vehicule_);
				plusLongTrajet.lireGraphe();
				std::cout << '\n';
			}
			else
			{
				std::cout << "Aucun vehicule n'a été enregistré, impossible d'extraire le sous-graphe";
			}
		}
		else if (option == 'd'){
			std::string depart, arrivee;
			std::cout << "La station de depart:";
			std::cin >> depart;
			std::cout << "La station d'arrivee:";
			std::cin >> arrivee;
			graphe_.plusCourtChemin(depart, arrivee, *vehicule_);
			std::cout << '\n';
		}
	}
}