#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#pragma once
#include "Produs.h"
using namespace std;

class Discuri:public Produs
{
    string casa_discuri,data_exp,trupa,numeA;
    const int constanta=5;
public:
    Discuri(string den,string d, int nr, double p,string c,string de,string t,string n):Produs(den,d,nr,p),casa_discuri(c),data_exp(de),trupa(t),numeA(n)
    {
      if (denumire != "CD" && denumire !="Vinil")
        throw invalid_argument("Denumire disc incorecta!");
    }
    double getPret() const override;
    void afisare() const override;
};


