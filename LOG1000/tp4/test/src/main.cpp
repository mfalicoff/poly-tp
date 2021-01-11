
#include <cppunit/ui/text/TestRunner.h>

// Fichiers contenant les tests
#include "test.h"

int main( int argc, char **argv)
{
    // Cr�e un objet pour ex�cuter les tests.
    // Va r�senter les r�sultats sous forme textuelle.
    CppUnit::TextUi::TestRunner runner;


    // La classe DiviseurTest contient des macros. 
    // Ces macros d�finissent une suite de tests.
    // Cela lui donne la m�thode statique "suite" qui est appel�e ici.
    // Cette m�thode statique retourne des pointeurs vers les m�thodes de tests.
    runner.addTest(Test::suite());

    // Ex�cute les tests et affiche les r�sultats.
    runner.run();

    return 0;
}
