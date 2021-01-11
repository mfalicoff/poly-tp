#ifndef ARC_H
#define ARC_H

#include <sommet.h>
#include <memory>

class Sommet;

class Arc {

public:
    Arc(std::shared_ptr<Sommet> sommet1, std::shared_ptr<Sommet> som2, int distance);

	//getters
    int distance() const;
    std::shared_ptr<Sommet> getSommetInitial() ;
    std::shared_ptr<Sommet> getSommetFinal();
	
    
private:
    int distance_;
    std::shared_ptr<Sommet> sommet1_;
    std::shared_ptr<Sommet> sommet2_;
};

#endif
