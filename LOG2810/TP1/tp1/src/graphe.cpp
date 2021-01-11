#include <graphe.h>


bool CompareSommets(Sommet sommet, std::string ident){
	auto sommetString = sommet.getIdent();
	return sommetString == ident;
}

Graphe::Graphe() {
	this->sommets_;
}

void Graphe::reset()
{
	sommets_.clear();
	arcs_.clear();
}

void Graphe::creerGraphe(std::string filename){
	
	std::ifstream file;
	std::string fullPath = filename;
	file.open(fullPath);


	if (file.fail())
		std::cout << "Erreur d'ouverture\n";
	else
	{
		while (file.peek() != '\n') {

			std::string ident;
			std::string type;

			std::getline(file, ident, ',');
			getline(file, type, ';');
			auto som = std::make_shared<Sommet>(Sommet(ident, type, 0));
			sommets_.push_back(som);
			sommets_[sommets_.size() - 1]->setIndex(sommets_.size() - 1);
		}

		file.ignore();

		while (file.peek() != '\n') {

			std::string arcDeparture;
			std::string arcArrival;
			int distance;

			std::getline(file, arcDeparture, ',');
			std::getline(file, arcArrival, ',');
			auto itSom1 = std::find_if(sommets_.begin(), sommets_.end(), [&arcDeparture](std::shared_ptr<Sommet>& som) {
				auto ok = som->getIdent();
				return ok == arcDeparture; 
				});

			auto itSom2 = std::find_if(sommets_.begin(), sommets_.end(), [&arcArrival](std::shared_ptr<Sommet>& som) {
				auto ok = som->getIdent();
				return ok == arcArrival;
				});
			file >> distance;

			auto sommetDepart = *itSom1;
			auto sommetArrivee = *itSom2;
			
			Arc newArc(sommetDepart, sommetArrivee, distance);
			auto arc = std::make_shared<Arc>(newArc);

			sommetDepart->ajouterVoisins(sommetArrivee);
			sommetArrivee->ajouterVoisins(sommetDepart);

			sommetDepart->ajouterArc(arc);
			arcs_.push_back(arc);

			file.ignore();
		}
	}
}


void Graphe::lireGraphe()
{
	std::cout << std::endl;
	for (auto& sommet : sommets_)
	{
		bool aSommet = false;
		bool afficherParenthese = false;
		std::cout << "(" << sommet->getIdent() << ", " << sommet->getType();

		for (auto& voisin : sommet->getListeVoisins())
		{
			if (afficherParenthese == false)
			{
				std::cout << ", (";
				afficherParenthese = true;
			}
			aSommet = true;
			std::cout << voisin->getIdent() << ", ";
		}
		if(aSommet == true)
			std::cout << '\b' << '\b' << ")";
		std::cout << ")\n";
	}
	std::cout << "\n" << std::endl;
}

bool isEveryNodeVisited(std::vector<bool>& vect) {
	for (auto val : vect) {
		if (val == false) {
			return false;
		}
	}
	return true;
}

Graphe Graphe::extractionGraphe(std::string sommetInit, std::unique_ptr<Vehicule>& vehicule) {

	Graphe nouveauGraphe;

	std::vector<bool> visited(sommets_.size(), false);
	auto itSom = std::find_if(sommets_.begin(), sommets_.end(), [&sommetInit](std::shared_ptr<Sommet>& som) {
		auto sommetString = som->getIdent();
		return sommetString == sommetInit;
		});
	auto root = *itSom;

	std::list<std::shared_ptr<Sommet>> tmp;
	std::list<std::shared_ptr<Sommet>> act;
	int maxDist = 0;
	int disact = 0;
	
	auto returnedPair = longestPath(root->getIndex(), visited, disact, maxDist, tmp, act, vehicule);
	auto listeSommets = returnedPair.first;

	//creation du nouveau grahe
	for (auto it = listeSommets.begin(); it != listeSommets.end(); ++it) {

		auto sommetOG = *it;
		Sommet nvSommet = *it->get();
		std::shared_ptr<Sommet>nv = std::make_shared<Sommet>(nvSommet);
		
		nouveauGraphe.sommets_.push_back(nv);
		nouveauGraphe.sommets_[nouveauGraphe.sommets_.size() - 1]->setIndex(nouveauGraphe.sommets_.size() - 1);

		//ajout des arcs
		auto arcsDuSommet = sommetOG->getListeArcs();
		if(std::next(it) != listeSommets.end()) {
			auto itSom1 = std::find_if(arcsDuSommet.begin(), arcsDuSommet.end(), [&](std::shared_ptr<Arc>& arc) {
				auto sommetInit = arc->getSommetInitial()->getIdent();
				auto sommetFinal = arc->getSommetFinal()->getIdent();
				auto prochainDeLaListe = *(++it);
				--it;
				return sommetInit == nv->getIdent() && sommetFinal == prochainDeLaListe->getIdent(); 
				});
			nv->ajouterArc(*itSom1);
			nv->ajouterVoisins((*itSom1)->getSommetFinal());
			nouveauGraphe.arcs_.push_back(*itSom1);
		}
	}
	return nouveauGraphe;
}

std::pair<std::list<std::shared_ptr<Sommet>>, int> Graphe::longestPath(int s, std::vector<bool> visited, int disAct, int& distMax, std::list<std::shared_ptr<Sommet>> tmpPath, std::list<std::shared_ptr<Sommet>>& maxPath, std::unique_ptr<Vehicule>& vehicule) {
	
	auto root = sommets_[s];
	visited[s] = true;
	tmpPath.push_back(root);

	//la liste de voisins est vide, chemin finit
	if(root->getListeArcs().empty()) {
		return std::make_pair(tmpPath, disAct);
	}

	//parcours des voisins
	for(auto& arc : root->getListeArcs()) {
		disAct += arc->distance();
		if(!visited[arc->getSommetFinal()->getIndex()]) {
			if(disAct <= vehicule->getMaxAutonomie()) {
				auto pair = longestPath(arc->getSommetFinal()->getIndex(), visited, disAct, distMax, tmpPath, maxPath, vehicule);
				if (pair.second > distMax) {
					distMax = pair.second;
					maxPath.clear();
					maxPath = pair.first;
				}
			}
			disAct -= arc->distance();
		}
	}
	return std::make_pair(maxPath, distMax);
}

void Graphe::ajouterSommet(std::shared_ptr<Sommet> sommet)
{}



void Graphe::plusCourtChemin(std::string sommetInit, std::string sommetFinal, Vehicule& vehicule)
{
	//Trouver les sommet � partir de leurs identifiants
	std::shared_ptr<Sommet> init = obtenirSommet(sommetInit);
	std::shared_ptr<Sommet> final = obtenirSommet(sommetFinal);
	if (init == nullptr || final == nullptr) { std::cout << "Mauvais sommets"; }

	//Les variables utiles � l'algorithme
	std::map<std::list<std::shared_ptr<Sommet>>, std::pair<int, Vehicule>> cheminsFixes;
	std::map<std::list<std::shared_ptr<Sommet>>, std::pair<int, Vehicule>> cheminsConnus;
	std::set<std::shared_ptr<Sommet>> sommetsAtteints;

	std::list<std::shared_ptr<Sommet>> chemin;
	chemin.push_back(init);
	auto cheminActuel = std::pair<std::list<std::shared_ptr<Sommet>>, std::pair<int, Vehicule>>(chemin, std::pair<int, Vehicule>(0, vehicule));
	cheminsFixes.insert(cheminActuel);
	sommetsAtteints.insert(init);

	//Continue tant que le dernier sommet du chemin n'est pas le sommet final
	while (cheminActuel.first.back() != final)
	{
		//Ajouter les chemins connues
		for (auto& arc : cheminActuel.first.back()->getListeArcs())
		{
			std::pair<std::list<std::shared_ptr<Sommet>>, std::pair<int, Vehicule>> cheminTampon = cheminActuel;

			int coutAutonomie = cheminTampon.second.second.getCoefAuto() * arc->distance();

			if (sommetsAtteints.find(arc->getSommetFinal()) == sommetsAtteints.end()
				&& coutAutonomie <= cheminTampon.second.second.getautonomieActuelle())
			{
				cheminTampon.second.second.setAutonomieActuelle(cheminTampon.second.second.getautonomieActuelle() - coutAutonomie);
				if ((cheminTampon.second.second.getType() == arc->getSommetFinal()->getType() 
					|| arc->getSommetFinal()->getType() == "hybride" 
					|| cheminTampon.second.second.getType() == "hybrid") && arc->getSommetFinal()->getType() != "rien")
				{
					cheminTampon.second.second.setAutonomieActuelle(cheminTampon.second.second.getMaxAutonomie());
				}
				cheminTampon.first.push_back(arc->getSommetFinal());
				cheminTampon.second.first += arc->distance();
				cheminsConnus.insert(cheminTampon);
			}
		}

		std::pair<std::list<std::shared_ptr<Sommet>>, std::pair<int, Vehicule>> minSommet = cheminActuel;


		if (cheminsConnus.size() == 0)
		{
			std::cout << "Aucun chemin trouve \n";
			return;
		}
		//Trouver et supprimer le chemin connue le plus petit
		auto min = std::min_element
		(
			cheminsConnus.begin(), cheminsConnus.end(),
			[](const std::pair<std::list<std::shared_ptr<Sommet>>, std::pair<int, Vehicule>>& p1,
				const std::pair<std::list<std::shared_ptr<Sommet>>, std::pair<int, Vehicule>>& p2) {
					return p1.second.first < p2.second.first;
			}
		);
		minSommet = *min;
		cheminsConnus.erase(min);

		


		//Verifier que le dernier sommet n'existe pas dans la liste de sommet atteints
		if ((sommetsAtteints.insert(minSommet.first.back())).second)
		{
			//Ajouter le chemin min aux chemins fixes
			cheminsFixes.insert(minSommet);
			//Changer le chemin actuel
			cheminActuel = minSommet;
		}
	}
	std::string sortie = "Chemin plus court trouve: ";
	for (auto& sommet : cheminActuel.first)
	{
		sortie += sommet->getIdent();
		sortie += "->";
	}

	vehicule = cheminActuel.second.second;

	sortie.pop_back();
	sortie.pop_back();
	std::cout << sortie;
	std::cout << "\n" << "Distance:" << cheminActuel.second.first;
	std::cout << "\n" << "Autonomie finale:" << cheminActuel.second.second.getautonomieActuelle() << "\n \n" ;
}

std::shared_ptr<Sommet> Graphe::obtenirSommet(std::string stringSommet)
{
	auto it = std::find_if(sommets_.begin(), sommets_.end(), [&stringSommet](const std::shared_ptr<Sommet>& obj) {return obj->getIdent() == stringSommet; });
	if (it == sommets_.end()){return nullptr;}
	int index = std::distance(sommets_.begin(), it);
	std::shared_ptr<Sommet> sommet = sommets_[index];
	return sommet;
}

bool Graphe::pairCompare(std::pair<std::list<std::shared_ptr<Sommet>>, int> i, std::pair<std::list<std::shared_ptr<Sommet>>, int> j)
{
	return i.second < j.second;
}

