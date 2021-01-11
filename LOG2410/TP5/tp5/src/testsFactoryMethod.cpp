#include "testsFactoryMethod.h"

using namespace std;

bool testConfigurationA() {
    ConfigurationArrosageA config = ConfigurationArrosageA();
    int qte = config.obtenirQuantiteArrosage(5, 5);
    bool qte1_ok = qte == 50;

    qte = config.obtenirQuantiteArrosage(10, 5);
    bool qte2_ok = qte == 100;

    qte = config.obtenirQuantiteArrosage(5, 20);
    bool qte3_ok = qte == 200;


    return (qte1_ok && qte2_ok && qte3_ok);
}

bool testConfigurationB() {
    ConfigurationArrosageB config = ConfigurationArrosageB();
    int qte = config.obtenirQuantiteArrosage(5, 5);
    bool qte1_ok = qte == 125;

    qte = config.obtenirQuantiteArrosage(10, 5);
    bool qte2_ok = qte == 175;

    qte = config.obtenirQuantiteArrosage(5, 20);
    bool qte3_ok = qte == 500;


    return (qte1_ok && qte2_ok && qte3_ok);
}

bool testConfigurationC() {
    ConfigurationArrosageC config = ConfigurationArrosageC();
    int qte = config.obtenirQuantiteArrosage(5, 5);
    bool qte1_ok = qte == 350;

    qte = config.obtenirQuantiteArrosage(10, 5);
    bool qte2_ok = qte == 575;

    qte = config.obtenirQuantiteArrosage(5, 20);
    bool qte3_ok = qte == 1400;


    return (qte1_ok && qte2_ok && qte3_ok);
}

bool testConfigurationParcelle() {
    ConfigurationArrosageA configA = ConfigurationArrosageA();
    ConfigurationArrosageB configB = ConfigurationArrosageB();
    ConfigurationArrosageC configC = ConfigurationArrosageC();

    Parcelle parcelle = Parcelle();
    int qte;

    parcelle.arroser(configA, 2, 2);
    qte = parcelle.obtenirHumidite();
    bool qte1_ok = (qte == 108);

    parcelle.arroser(configB, 3, 3);
    qte = parcelle.obtenirHumidite();
    bool qte2_ok = (qte == 171);

    parcelle.arroser(configC, 4, 4);
    qte = parcelle.obtenirHumidite();
    bool qte3_ok = (qte == 415);

    return (qte1_ok && qte2_ok && qte3_ok);
}