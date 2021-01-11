#include "testsDecorateur.h"

bool testJardinDecorateur() {
    Parcelle* parcelle = new Parcelle();
    JardinDecorateur jardin = JardinDecorateur(parcelle);

    jardin.simulerTranspiration();
    bool humidite_ok = (parcelle->obtenirHumidite() == 85);

    delete parcelle;

    return humidite_ok;

}

bool testPelouseDecorateur() {
    Parcelle* parcelle = new Parcelle();
    PelouseDecorateur pelouse = PelouseDecorateur(parcelle, 12);

    pelouse.simulerTranspiration();
    bool humidite_ok = (parcelle->obtenirHumidite() == 78);

    delete parcelle;

    return humidite_ok;
}

bool testPotagerDecorateur() {
    Parcelle* parcelle = new Parcelle();
    PotagerDecorateur potager = PotagerDecorateur(parcelle, 3);

    potager.simulerTranspiration();
    bool humidite_ok = (parcelle->obtenirHumidite() == 75);

    delete parcelle;

    return humidite_ok;
}

bool testMultipleDecorateur() {
    Parcelle* parcelle = new Parcelle();
    JardinDecorateur* jardin = new JardinDecorateur(parcelle);
    PotagerDecorateur* potagerEtJardin = new PotagerDecorateur(jardin, 3);
    PelouseDecorateur multipleTerrain = PelouseDecorateur(potagerEtJardin, 12);

    multipleTerrain.simulerTranspiration();

    bool humidite_ok = (parcelle->obtenirHumidite() == 58);

    delete potagerEtJardin;
    delete jardin;
    delete parcelle;

    return humidite_ok;

}
