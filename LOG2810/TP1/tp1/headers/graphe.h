#ifndef GRAPHE_H
#define GRAPHE_H

#include <string>
#include <list>
#include <sommet.h>
#include <memory>
#include <vehicule.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <map>


class Graphe {

public:

	Graphe();
	

	//methodes
	void reset();
    void creerGraphe(std::string filename);
	void lireGraphe();
	
	void plusCourtChemin(std::string sommetInit, std::string sommetFinal, Vehicule& vehicule);
	Graphe extractionGraphe(std::string sommetInit, std::unique_ptr<Vehicule>& vehicule);
	
	//getters
	std::shared_ptr<Sommet> obtenirSommet(std::string stringSommet);
	//setters
	void ajouterSommet(std::shared_ptr<Sommet> sommet);

private:
	bool pairCompare(std::pair<std::list<std::shared_ptr<Sommet>>, int> i, std::pair<std::list<std::shared_ptr<Sommet>>, int> j);
	std::pair<std::list<std::shared_ptr<Sommet>>, int> longestPath(int s, std::vector<bool> visited, int disAct, int& distMax, std::list<std::shared_ptr<Sommet>> tmpPath, std::list<std::shared_ptr<Sommet>>& maxPath, std::unique_ptr<Vehicule>& vehicule);
    std::vector<std::shared_ptr<Sommet>> sommets_;
	std::vector<std::shared_ptr<Arc>> arcs_;
};

#endif
