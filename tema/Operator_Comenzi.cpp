#include "Operator_Comenzi.h"
using namespace std;

void Operator_Comenzi::adaugaComanda(shared_ptr<Comenzi> comanda)
{
    if (comenziActive.size() < 3)
    {
        comenziActive.push(comanda); // Folosește shared_ptr
        cout << "Comanda cu ID-ul " << comanda->getID() << " a fost asignata operatorului " << getID() << endl;
    }
    else
    {
        throw std::invalid_argument("Operatorul nu poate gestiona mai mult de 3 comenzi simultan");
    }
}

void Operator_Comenzi::adaugaComandaFinalizata(shared_ptr<Comenzi> comanda)
{
    comenziFinalizate.push_back(comanda);
    nrComenziProcesate++;
}

double Operator_Comenzi:: getSalariu() const
{
    double salariu= Salariu_Baza * coeficient + 100 * getAniVechime();
    if(esteZiuaAngajatului())
        salariu=salariu+100;
    double bonus = 0.0;
    // Calculez bonusul din comenzile finalizate
    for (const auto& comanda : comenziFinalizate)
        bonus += comanda->getValoare() * 0.005;
    return salariu + bonus;
}
