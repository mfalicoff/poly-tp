#include <iostream>
#include "tp4Tests.h"

int main() {
    std::cout << "Bienvenue au module principal de contrôle de votre système Polyjet." << std::endl << std::endl;
    std::cout << "TESTS" << std::endl << "-------------------------------------" << std::endl;

    testSuiteComposite();
    std::cout << "-------------------------------------" << std::endl;
    testSuiteDecorateur();
    std::cout << "-------------------------------------" << std::endl;
    return 0;
}