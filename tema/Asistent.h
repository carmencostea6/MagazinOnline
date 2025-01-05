#include <iostream>
#include <string>
#include <string.h>
#include "Angajat.h"
#pragma once
using namespace std;

class Asistent:public Angajat
{
private:
    const double  coeficient=0.75;
public:
    Asistent(int i,string n, string p, string c,string d):Angajat(i,n,p,c,d)
    {

    }
    double getSalariu() const override;
};

