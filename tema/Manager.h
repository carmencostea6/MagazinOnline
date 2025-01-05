#include "Angajat.h"
#pragma once
using namespace std;

class Manager:public Angajat
{
private:
     const double  coeficient=1.25;
public:
    Manager(int i,string n, string p, string c,string d):Angajat(i,n,p,c,d)
    {

    }
    double getSalariu() const override;
};
