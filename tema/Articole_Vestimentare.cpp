#include "Articole_Vestimentare.h"
using namespace std;

 double Articole_Vestimentare::getPret() const
 {
     return pret_baza+constanta;
 }
void Articole_Vestimentare::afisare() const
{
    Produs::afisare();
    cout<<"Culoarea: "<<culoare<<", Marca: "<< marca<< " si pretul final: "<<getPret()<<endl;
}
