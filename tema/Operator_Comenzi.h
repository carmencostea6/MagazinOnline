#include <iostream>
#include <string>
#include <string.h>
#include "Angajat.h"
#pragma once
#include <queue>
#include "Comenzi.h"
#include <memory>
using namespace std;

class Operator_Comenzi:public Angajat
{
private:
    const double coeficient=1.00;
    queue<shared_ptr<Comenzi>> comenziActive;
    vector<shared_ptr<Comenzi>> comenziFinalizate;
    int nrComenziProcesate=0;
public:
    Operator_Comenzi()=default;
    Operator_Comenzi(int i,string n, string p, string c,string d):Angajat(i,n,p,c,d)
    {

    }
    double getSalariu() const override; //NU UITA DE 0.5% DIN COMENZI
    void adaugaComanda(shared_ptr<Comenzi> comanda);
    bool esteDisponibil() const
    {
        return comenziActive.size()<3;
    }
     queue<shared_ptr<Comenzi>>& getComenziActive()
    {
        return comenziActive;
    }
    void adaugaComandaFinalizata(shared_ptr<Comenzi> );
    int getNrComenziActive() const
    {
        return comenziActive.size();
    }
    int getNrComenziProcesate() const
    {
        return nrComenziProcesate;
    }
    const vector<shared_ptr<Comenzi>>& getComenziFinalizate() const
{
    return comenziFinalizate;
}

};

