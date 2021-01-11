#include "testHelper.h"

void afficherTestResultat(string nomTest, bool estReussi) {
    if(estReussi) {
        cout << "Le test " << nomTest << " a RÉUSSI" << endl;
    } else {
        cout << "Le test " << nomTest << " a ÉCHOUÉ" << endl;
    }
}
