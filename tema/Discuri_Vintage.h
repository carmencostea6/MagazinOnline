#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#pragma once
#include "Produs.h"
using namespace std;

class Discuri_Vintage:public Produs
{
    bool mint;
    int rar;
    const int constantaD=5;
    const int constanta=15;
public:
    Discuri_Vintage(string den,string d, int nr, double p,bool m, int r):Produs(den,d,nr,p),mint(m), rar(r)
    {
      if(rar<1 || rar>5)
        throw invalid_argument("Coeficient de raritate gresit!");
        if (denumire != "CD" && denumire !="Vinil")
        throw invalid_argument("Denumire disc vintage incorecta!");
    }
    double getPret() const override;
    void afisare() const override;
};


