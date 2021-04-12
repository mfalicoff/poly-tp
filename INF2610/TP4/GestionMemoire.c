// Anthony Marcelo Guzman Soto 2019666
// Maximiliano Falicoff 2013658
#include "./libs/lib.h"
#define TAILLE_PAGE 1024

unsigned int calculerNumeroDePage(unsigned long adresse) {
    return adresse / TAILLE_PAGE;
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse) {
     return adresse % TAILLE_PAGE;
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage) {
     return numeroDePage * TAILLE_PAGE + deplacementDansLaPage;
}

void rechercherTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	unsigned int numeroDePageRequete= calculerNumeroDePage(req->adresseVirtuelle);
	unsigned int deplacementDansLaPage = calculerDeplacementDansLaPage(req->adresseVirtuelle);
	//on veut chercher dans tout le tlb
	for(int i=0; i<TAILLE_TLB; i++)
	{
		//On veut s'assurer que la page qu'on cherche est situe dans le tlb
		if(mem->tlb->numeroPage[i]==numeroDePageRequete && mem->tlb->entreeValide[i]==1)
		{
			req->adressePhysique= calculerAdresseComplete(mem->tlb->numeroCadre[i], deplacementDansLaPage);
			req->estDansTLB = 1;
			mem->tlb->dernierAcces[i]= req->date;
			return;
		}
	}
	//si la page n est pas dans le tlb
	req->adressePhysique=0;
	req->estDansTLB = 0;

}

void rechercherTableDesPages(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	unsigned int page = calculerNumeroDePage(req->adresseVirtuelle);
	unsigned long deplacement = calculerDeplacementDansLaPage(req->adresseVirtuelle);
	
	if(mem->tp->entreeValide[page] == 1){
		req->adressePhysique = calculerAdresseComplete(mem->tp->numeroCadre[page], deplacement);
	}else{
		req->adressePhysique = 0;
	}
	
}

void ajouterDansMemoire(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	
	int numeroDePageRequete= calculerNumeroDePage(req->adresseVirtuelle);
	unsigned long deplacementDansLaPage = calculerDeplacementDansLaPage(req->adresseVirtuelle);
	
	// parcours memoire
	for(int i=0; i<TAILLE_MEMOIRE;i++)
	{
		if(mem->memoire->utilisee[i]==0)
		{
			// insertion
			req->adressePhysique= calculerAdresseComplete(i,deplacementDansLaPage);
			mem->memoire->numeroPage[i]= numeroDePageRequete;
			mem->memoire->dateCreation[i]= req->date;
			mem->memoire->dernierAcces[i]= req->date;
			mem->memoire->utilisee[i]=1;
			break;
		}
	}

	
}

void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	int positionFifo = 0;

	for(int pos = 0; pos < TAILLE_TLB; pos++){
		
		// tlb vide
		if(mem->tlb->entreeValide[pos] == 0){
			mem->tlb->entreeValide[pos] = 1;
			mem->tlb->dateCreation[pos] = req->date;
			mem->tlb->dernierAcces[pos] = req->date;
			mem->tlb->numeroPage[pos] = calculerNumeroDePage(req->adresseVirtuelle);
			mem->tlb->numeroCadre[pos] = calculerNumeroDePage(req->adressePhysique);
			break;
		}
		//tlb remplie, on recherche le plus jeune
		 else if(mem->tlb->dateCreation[pos] < mem->tlb->dateCreation[positionFifo]){
			positionFifo = pos;
		}

		// remplacement par le fi de fifo
		mem->tlb->entreeValide[positionFifo] = 1;
		mem->tlb->dateCreation[positionFifo] = req->date;
		mem->tlb->dernierAcces[positionFifo] = req->date;
		mem->tlb->numeroPage[positionFifo] = calculerNumeroDePage(req->adresseVirtuelle);
		mem->tlb->numeroCadre[positionFifo] = calculerNumeroDePage(req->adressePhysique);
		
	}
	
}

// NE PAS MODIFIER
int main() {
    evaluate(
		&calculerNumeroDePage, 
		&calculerDeplacementDansLaPage, 
		&calculerAdresseComplete, 
        &rechercherTLB, 
		&rechercherTableDesPages,
		&mettreAJourTLB,
		&ajouterDansMemoire
    );
    return 0;
}
