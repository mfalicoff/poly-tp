#include "testsComposite.h"

using namespace std;

bool testAjouterComposite() {
    CompositeParcelle* composite = new CompositeParcelle();
    Parcelle* parcelle1 = new Parcelle();
    Parcelle* parcelle2 = new Parcelle();
    Parcelle* parcelle3 = new Parcelle();

    composite->ajouterParcelle(parcelle1);
    composite->ajouterParcelle(parcelle2);
    composite->ajouterParcelle(parcelle3);

    list<AbsParcelle*> parcelles = composite->obtenirParcellesEnfant();

    bool parcelle1Presente = (find(parcelles.begin(), parcelles.end(), parcelle1) != parcelles.end());
    bool parcelle2Presente = (find(parcelles.begin(), parcelles.end(), parcelle2) != parcelles.end());
    bool parcelle3Presente = (find(parcelles.begin(), parcelles.end(), parcelle3) != parcelles.end());
    bool tailleCorrecte = parcelles.size() == 3;

    delete composite;
    delete parcelle1;
    delete parcelle2;
    delete parcelle3;

    return (parcelle1Presente && parcelle2Presente && parcelle3Presente && tailleCorrecte);
}

bool testEnleverComposite() {
    CompositeParcelle* composite = new CompositeParcelle();
    Parcelle* parcelle1 = new Parcelle();
    Parcelle* parcelle2 = new Parcelle();
    Parcelle* parcelle3 = new Parcelle();

    composite->ajouterParcelle(parcelle1);
    composite->ajouterParcelle(parcelle2);
    composite->ajouterParcelle(parcelle3);
    composite->enleverParcelle(parcelle2);

    list<AbsParcelle*> parcelles = composite->obtenirParcellesEnfant();

    bool parcelle1Presente = (find(parcelles.begin(), parcelles.end(), parcelle1) != parcelles.end());
    bool parcelle2Absente = !(find(parcelles.begin(), parcelles.end(), parcelle2) != parcelles.end());
    bool parcelle3Presente = (find(parcelles.begin(), parcelles.end(), parcelle3) != parcelles.end());
    bool tailleCorrecte = parcelles.size() == 2;

    delete composite;
    delete parcelle1;
    delete parcelle2;
    delete parcelle3;

    return (parcelle1Presente && parcelle2Absente && parcelle3Presente && tailleCorrecte);
}

bool testAjouterPlusieursNiveauxComposite() {
    CompositeParcelle* composite = new CompositeParcelle();
    Parcelle* parcelle1 = new Parcelle();
    Parcelle* parcelle2 = new Parcelle();
    Parcelle* parcelle3 = new Parcelle();
    Parcelle* parcelle4 = new Parcelle();
    Parcelle* parcelle5 = new Parcelle();

    composite->ajouterParcelle(parcelle1);
    composite->ajouterParcelle(parcelle2);
    composite->ajouterParcelle(parcelle3);

    CompositeParcelle* sousComposite = new CompositeParcelle();
    sousComposite->ajouterParcelle(parcelle4);
    sousComposite->ajouterParcelle(parcelle5);

    composite->ajouterParcelle(sousComposite);

    list<AbsParcelle*> parcelles = composite->obtenirParcellesEnfant();
    list<AbsParcelle*> sousparcelles = sousComposite->obtenirParcellesEnfant();

    bool parcelle1Presente = (find(parcelles.begin(), parcelles.end(), parcelle1) != parcelles.end());
    bool parcelle2Presente = (find(parcelles.begin(), parcelles.end(), parcelle2) != parcelles.end());
    bool parcelle3Presente = (find(parcelles.begin(), parcelles.end(), parcelle3) != parcelles.end());
    bool sousCompositePresente = (find(parcelles.begin(), parcelles.end(), sousComposite) != parcelles.end());
    bool taillesCorrectes = parcelles.size() == 4 && sousparcelles.size() == 2;
    
    delete composite;
    delete parcelle1;
    delete parcelle2;
    delete parcelle3;
    delete parcelle4;
    delete parcelle5;
    delete sousComposite;

    return (
        parcelle1Presente
        && parcelle2Presente
        && parcelle3Presente
        && sousCompositePresente
        && taillesCorrectes
    );
}

bool testCompositeRecursif() {
    CompositeParcelle* composite = new CompositeParcelle();
    CompositeParcelle* sousComposite1 = new CompositeParcelle();
    CompositeParcelle* sousComposite2 = new CompositeParcelle();
    CompositeParcelle* sousSousComposite = new CompositeParcelle();

    Parcelle* parcelle1 = new Parcelle();
    Parcelle* sousParcelle1 = new Parcelle();
    Parcelle* sousParcelle2 = new Parcelle();
    Parcelle* sousSousParcelle1 = new Parcelle();
    Parcelle* sousSousParcelle2 = new Parcelle();


    composite->ajouterParcelle(parcelle1);
    sousComposite1->ajouterParcelle(sousParcelle1);
    sousComposite2->ajouterParcelle(sousParcelle2);
    sousSousComposite->ajouterParcelle(sousSousParcelle1);
    sousSousComposite->ajouterParcelle(sousSousParcelle2);

    composite->ajouterParcelle(sousComposite1);
    composite->ajouterParcelle(sousComposite2);

    sousComposite1->ajouterParcelle(sousSousComposite);

    composite->simulerTranspiration();
    sousComposite1->simulerTranspiration();
    sousSousParcelle2->simulerTranspiration();

    bool transpiration1_ok = parcelle1->obtenirHumidite() == 90;
    bool transpiration2_ok = sousParcelle1->obtenirHumidite() == 80;
    bool transpiration3_ok = sousParcelle2->obtenirHumidite() == 90;
    bool transpiration4_ok = sousSousParcelle1->obtenirHumidite() == 80;
    bool transpiration5_ok = sousSousParcelle2->obtenirHumidite() == 70;

    delete composite;
    delete sousComposite1;
    delete sousComposite2;
    delete sousSousComposite;
    delete parcelle1;
    delete sousParcelle1;
    delete sousParcelle2;
    delete sousSousParcelle1;
    delete sousSousParcelle2;

    return (
        transpiration1_ok
        && transpiration2_ok
        && transpiration3_ok
        && transpiration4_ok
        && transpiration5_ok
    );

}
