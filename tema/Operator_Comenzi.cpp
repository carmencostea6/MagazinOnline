#include "Operator_Comenzi.h"
using namespace std;
double Operator_Comenzi:: getSalariu() const
{
    //NU UITA DE 0.5% DIN COMENZI
    double salariu= Salariu_Baza * coeficient + 100 * getAniVechime();
    if(esteZiuaAngajatului())
        salariu=salariu+100;
    return salariu;
}

