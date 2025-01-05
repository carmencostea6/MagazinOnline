#include "Discuri.h"
using namespace std;

 double Discuri::getPret() const
 {
     return pret_baza+constanta;
 }
void Discuri::afisare() const
{
    Produs::afisare();
    cout<<"Casa de Discuri: "<< casa_discuri<<", data punere in vanzare: "<<data_exp<<", Trupa:" <<trupa<< ", Nume Album: "<<numeA <<" si pretul final: "<<getPret()<<endl;
}
