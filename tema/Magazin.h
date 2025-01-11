#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
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
#include "Comenzi.h"
#include <thread>
#include <chrono>
#include <memory>
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

    bool alldone = 0;
    queue<shared_ptr<Comenzi>> comenzi;
    queue<shared_ptr<Comenzi>> comenziAsteptare;
    bool actualizeazaStoc(const vector<shared_ptr<Produs>>& , const vector<int>& );
    bool validareComanda(const vector<shared_ptr<Produs>>& , const vector<int>& ) const;
public:
    Magazin()=default;
    static string getDataCurenta();

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

    Produs* cautaProdus(int cod);
    Angajat* cautaOperator();
    void citesteComenzi(ifstream &);
    void adaugaComanda(const vector<shared_ptr<Produs>>& ,const vector<int>& , int , const string& );
    void comenziInAsteptare();
    void procesare();

    void celeMaiMulteComenzi(ofstream &);
    void celeMaiValoroaseComenzi(ofstream& );
    void celMaiMareSalariu(ofstream &);

    ~Magazin();
};
