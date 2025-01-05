#include "Discuri_Vintage.h"
using namespace std;

 double Discuri_Vintage::getPret() const
 {
     return pret_baza+constantaD+constanta*rar;
 }
void Discuri_Vintage::afisare() const
{
    Produs::afisare();
    cout<<"Este Mint: "<<mint<<", Coeficientul de Raritate: "<< rar<< " si pretul final: "<<getPret()<<endl;
}
