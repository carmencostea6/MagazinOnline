#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include<limits>
#pragma once
#include "Angajat.h"
#include "Manager.h"
#include "Operator_Comenzi.h"
#include "Asistent.h"
#include "Articole_Vestimentare.h"
#include "Discuri.h"
#include "Discuri_Vintage.h"
using namespace std;
class Magazin
{
    vector<Angajat*> angajati;//pastrez polimorfismul-exista metode virtuale pure in clasa Angajat
    bool idUnic(int );
    inline static int nrManageri=0;
    inline static int nrOperatori=0;
    inline static int nrAsistenti=0;

    vector<Produs*> produse;
    inline static int nrHaine=0;
    inline static int nrDiscuri=0;
    inline static int nrVintage=0;
public:
    Magazin()=default;

    void citesteAngajati(ifstream &);
    void adaugaAngajat();
    void stergeAngajat(int );//voi sterge Angajatul dupa ID
    void modificaNumeAngajat(int,string &);//modific numele Angajatului dupa ID
    void afisareAngajat(int ) const;
    void afisareAngajati()const;

    void citesteProduse(istream &);
    void adaugaProdus();
    void stergeProdus(int );//sterg produsul dupa cod
    void modificaNrProduse(int, int);
    void afisareProdus(int )const;
    void afisareProduse() const;

    bool verifica() const;
    ~Magazin();
};
