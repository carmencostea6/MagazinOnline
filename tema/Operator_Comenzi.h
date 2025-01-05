#include <iostream>
#include <string>
#include <string.h>
#include "Angajat.h"
#pragma once
using namespace std;

class Operator_Comenzi:public Angajat
{
private:
    const double coeficient=1.00;
public:
    Operator_Comenzi(int i,string n, string p, string c,string d):Angajat(i,n,p,c,d)
    {

    }
    double getSalariu() const override; //NU UITA DE 0.5% DIN COMENZI
};

