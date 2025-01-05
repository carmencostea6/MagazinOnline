#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#pragma once
#include "Produs.h"
using namespace std;

class Articole_Vestimentare:public Produs
{
    string culoare, marca;
    const int constanta=20;
public:
    Articole_Vestimentare(string den,string d, int nr, double p,string c,string m):Produs(den,d,nr,p),culoare(c),marca(m)
    {

    }
    double getPret() const override;
    void afisare() const override;
};

