#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#pragma once
using namespace std;

class Angajat
{
protected:
    const int ID;
    string nume;
    string prenume;
    string CNP;
    string dataAngajarii; //in format ZZ/LL/AAAA

    inline static const double Salariu_Baza=3500.00;

    void CNPvalid();
    void Numevalid();

    int getAniVechime() const;
    bool esteZiuaAngajatului() const;
public:
    Angajat(int i,string n, string p, string c,string d):ID(i),nume(n),prenume(p),CNP(c),dataAngajarii(d)
    {
        Numevalid();
        CNPvalid();
        if(!esteMajor())
            throw invalid_argument("Nu angajam persoane minore!");
    }
    virtual double getSalariu() const=0;
    virtual void afisare() const
    {
        cout << "ID:" <<ID<< ", Nume:" <<nume<<", Prenume:"<<prenume<<", CNP:"<<CNP<<", Data angajarii:" <<dataAngajarii<<", Salariu: "<< getSalariu()<<" RON"<< endl;
    }

    int getID()const
    {
        return ID;
    }
    void setNume(string &);
    bool esteMajor() const;

    virtual ~Angajat()
    {

    }

};

