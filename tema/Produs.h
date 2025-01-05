#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#pragma once
using namespace std;

class Produs
{
protected:
    string denumire, data_int;
    int nr_produse,cod;
    double pret_baza;
    inline static int codProd=0; //cod unic asignat fiecarui produs!
public:
    Produs(string den,string d,int nr,double p):denumire(den),data_int(d),nr_produse(nr),pret_baza(p),cod(++codProd)
    {
    }
    virtual double getPret() const=0;
    int getCod()const
    {
        return cod;
    }
    virtual void afisare()const
    {
        cout<<" Denumire produs: " << denumire << ", data adaugarii in stoc: "<<  data_int << ", nr. produse in stoc: " << nr_produse<< ", pret de baza: " << pret_baza <<", cod:" << cod <<endl;
    }
    void setNrProd(int nr)
    {
        if (nr < 0)
            throw invalid_argument("Numarul de produse nu poate fi negativ");
        nr_produse=nr;
    }
    virtual ~Produs()
    {

    }

};
