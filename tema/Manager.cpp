#include "Manager.h"
using namespace std;

double Manager:: getSalariu() const
{
    return Salariu_Baza * coeficient + 100 * getAniVechime();
}
