#include "arc.h"

Arc::Arc(std::shared_ptr<Sommet> sommet1, std::shared_ptr<Sommet> som2, int distance) : distance_(distance), sommet1_(sommet1), sommet2_(som2) {};

int Arc::distance() const {
	return distance_;
}

std::shared_ptr<Sommet> Arc::getSommetInitial()  {
	return sommet1_;
}

std::shared_ptr<Sommet> Arc::getSommetFinal()  {
	return sommet2_;
}




