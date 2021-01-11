#include <iostream>
#include "tp4Tests.h"
#include "tp5Tests.h"

#define _ std::cout << "-------------------------------------" << std::endl

int main() {
    std::cout << "Bienvenue au module principal de contrôle de votre système Polyjet." << std::endl << std::endl;
    std::cout << "TESTS" << std::endl << "-------------------------------------" << std::endl;
    /* tests du tp4
    testSuiteComposite();
    _;
    testSuiteDecorateur();
    _;
    */
   // tests du tp5
    testSuiteTemplateMethod();
    _;
    testSuiteFactoryMethod();
    _;
    

    return 0;
}