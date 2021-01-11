#include "tp5Tests.h"

void testSuiteFactoryMethod() {
    cout << "--- Tests sur le patron factory method ---" << endl;
    afficherTestResultat("testConfigurationA", testConfigurationA());
    afficherTestResultat("testConfigurationB", testConfigurationB());
    afficherTestResultat("testConfigurationC", testConfigurationC());
    afficherTestResultat("testConfigurationParcelle", testConfigurationParcelle());
}

void testSuiteTemplateMethod() {
    cout << "--- Tests sur le patron template method ---" << endl;
    afficherTestResultat("testArrosoirOscillant", testArrosoirOscillant());
    afficherTestResultat("testArrosoirRotatif", testArrosoirRotatif());
}
