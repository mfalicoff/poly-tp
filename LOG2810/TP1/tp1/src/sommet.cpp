#include "sommet.h"
#include <string>

Sommet::Sommet(std::string ident, std::string type, int index) : identifiant_(ident), type_(type), index_(index)
{
}

Sommet::Sommet(const Sommet& sommet) {
	identifiant_ = sommet.getIdent();
	type_ = sommet.type_;
}

bool Sommet::operator==( std::string type) const{
	if(type == this->type_) {
		return true;
	}
	return false;
}

bool operator==(std::string type,const Sommet& sommet) {
	return sommet == type;
}

void Sommet::ajouterVoisins(std::shared_ptr<Sommet> sommet) {

	if(std::find_if(voisins_.begin(), voisins_.end(), [&sommet](std::shared_ptr<Sommet>& som) {
		auto ok = som->getIdent();
		auto ok1 = sommet->getIdent();
		return ok1 == ok;
		}) == voisins_.end()) {
		voisins_.push_back(sommet);
	}
}

void Sommet::setIndex(int index)
{
	index_ = index;
}

int Sommet::getIndex() {
	return index_;
}


void Sommet::ajouterArc(std::shared_ptr<Arc> arc) {
	arcs_.push_back(arc);
}

std::string Sommet::getIdent() const {
	return identifiant_;
}

std::vector<std::shared_ptr<Arc>>& Sommet::getListeArcs()
{
	return arcs_;
}

std::vector<std::shared_ptr<Sommet>> Sommet::getListeVoisins() {
	return voisins_;
}

std::string Sommet::getType() const {
	return type_;
}


