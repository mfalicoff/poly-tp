#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <vehicule.h>
#include <graphe.h>
#include <memory>

class Interface{

public:

	Interface();

	//methodes
	void menu();

private:
	std::unique_ptr<Vehicule> vehicule_;
	Graphe graphe_;
};

#endif
