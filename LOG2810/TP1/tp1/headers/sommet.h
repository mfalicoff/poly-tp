#ifndef SOMMET_H
#define SOMMET_H

#include <string>
#include <list>
#include <arc.h>
#include <memory>
#include <vector>

class Arc;
class Sommet {

public:
	
    Sommet(std::string ident, std::string type, int index);
    Sommet(const Sommet& sommet);
	
    bool operator==( std::string type) const;
    friend bool operator==(std::string type, const Sommet& sommet);

	// methods
    void ajouterVoisins(std::shared_ptr<Sommet> sommet);
    void ajouterArc(std::shared_ptr<Arc> arc);

	//getters
    std::string getIdent() const;
    std::vector<std::shared_ptr<Arc>>& getListeArcs() ;
    std::vector<std::shared_ptr<Sommet>> getListeVoisins();
    std::string getType() const;
    void setIndex(int index);
    int getIndex();
 
private:
    int index_;
    std::vector<std::shared_ptr<Sommet>> voisins_;
    std::vector<std::shared_ptr<Arc>> arcs_;
    std::string identifiant_;
    std::string type_;
};

#endif
