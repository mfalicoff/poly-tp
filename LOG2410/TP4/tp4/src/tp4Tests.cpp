#include "tp4Tests.h"


void testSuiteComposite() {
    cout << "--- Tests sur le patron composite ---" << endl;
    afficherTestResultat("testAjouterComposite", testAjouterComposite());
    afficherTestResultat("testEnleverComposite", testEnleverComposite());
    afficherTestResultat("testAjouterPlusieursNiveauxComposite", testAjouterPlusieursNiveauxComposite());
    afficherTestResultat("testCompositeRecursif", testCompositeRecursif());
}

void testSuiteDecorateur() {
    cout << "--- Tests sur le patron decorateur --" << endl;
    afficherTestResultat("testJardinDecorateur", testJardinDecorateur());
    afficherTestResultat("testPelouseDecorateur", testPelouseDecorateur());
    afficherTestResultat("testPotagerDecorateur", testPotagerDecorateur());
    afficherTestResultat("testMultipleDecorateur", testMultipleDecorateur());
}
