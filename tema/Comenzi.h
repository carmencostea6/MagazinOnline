#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#include <vector>
#include <memory>
#pragma once
#include "Produs.h"
using namespace std;
class Comenzi
{
    int IDcomanda;
    string data;
    int durata;
    int durataRamasa;
    double valoare;
    vector<shared_ptr<Produs>> produse;
    inline static int IDnr=0;
public:
    Comenzi(const string& d, int t, const vector<shared_ptr<Produs>>& P , double val): data(d), durata(t),durataRamasa(t), produse(P), valoare(val),IDcomanda(++IDnr)
    {

    }
    double getValoare() const
    {
        return valoare;
    }
    int getID() const
    {
        return IDcomanda;
    }
    int getDurata() const
    {
        return durata;
    }
    string getData() const
    {
        return data;
    }
    const vector<shared_ptr<Produs>>& getProduse() const
    {
        return produse;
    }
    void decrementDurataRamasa()
    {
        if (durataRamasa > 0)
            durataRamasa--;
    }
    int getDurataRamasa() const
    {
        return durataRamasa;
    }
    bool esteFinalizata() const
    {
        return durataRamasa <= 0;
    }
};
