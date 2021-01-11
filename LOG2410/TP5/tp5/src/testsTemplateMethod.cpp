#include "testsTemplateMethod.h"

using namespace std;

bool testArrosoirOscillant() {
    ArrosoirOscillant osc1 = ArrosoirOscillant(5, 5);
    ArrosoirOscillant osc2 = ArrosoirOscillant(3, 6);
    int qte;

    qte = osc1.activer(3, 3);
    bool qte1_ok = (qte == 84);

    qte = osc2.activer(3, 3);
    bool qte2_ok = (qte == 63);

    return (qte1_ok && qte2_ok);

}

bool testArrosoirRotatif() {
    ArrosoirRotatif osc1 = ArrosoirRotatif(5);
    ArrosoirRotatif osc2 = ArrosoirRotatif(6);
    int qte;

    qte = osc1.activer(3, 3);
    bool qte1_ok = (qte == 45);

    qte = osc2.activer(3, 3);
    bool qte2_ok = (qte == 54);

    return (qte1_ok && qte2_ok);
}
