#include "Asistent.h"
using namespace std;
double Asistent:: getSalariu() const
{
    double salariu= Salariu_Baza * coeficient + 100 * getAniVechime();
    if(esteZiuaAngajatului())
        salariu=salariu+100;
    return salariu;
}


