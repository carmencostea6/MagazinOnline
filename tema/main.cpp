#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include "Magazin.h"

#include "Angajat.h"
#include "Manager.h"
#include "Operator_Comenzi.h"
#include "Asistent.h"


#include "Produs.h"
#include "Articole_Vestimentare.h"
#include "Discuri.h"
#include "Discuri_Vintage.h"
using namespace std;


int main()
{
    Magazin magazin;
    ifstream f("angajati.txt");
    if (!f)
        cout << "Eroare: Fisierul angajati.txt nu a putut fi deschis"<<endl;
    else
    {
        try
        {
            magazin.citesteAngajati(f);
        }
        catch (const exception& e)
        {
            cout << "Eroare: " << e.what() << endl;
        }
        f.close();
    }
    ifstream g("produse.txt");
    if (!g)
        cout<< "Eroare: Fisierul produse.txt nu a putut fi deschis"<<endl;
    else
    {
        try
        {
            magazin.citesteProduse(g);
        }
        catch( const exception& e)
        {
            cout<< "Eroare:"  <<e.what()<< endl;
        }
        g.close();
    }
    bool continuaA=1;
    bool continuaB=1;
    bool continua = 1;
    if(magazin.verifica()==0)//daca nu respect conditiile de functionare ale magazinului ma opresc
    {
        continuaA=0;
        continuaB=0;
        continua=0;
    }
    while (continua)
    {
        cout << "MENIU PRINCIPAL" << endl;
        cout << "1. Gestionare angajati" << endl;
        cout << "2. Gestionare stoc" << endl;
        cout << "0. Iesire" << endl;
        cout << "Introduceti optiunea: ";
        int optiune;
        cin >> optiune;

        if (optiune == 1)
        {
            bool continuaA = true;
            do
            {
                cout << "MENIU GESTIONARE ANGAJATI"<<endl;
                cout << "1. Adauga angajat de la tastatura"<<endl;
                cout << "2. Sterge un angajat dupa ID"<<endl;
                cout << "3. Modifica numele unui angajat"<<endl;
                cout << "4. Afiseaza datele unui angajat dupa ID"<<endl;
                cout << "5. Afiseaza toti angajatii"<<endl;
                cout << "0. Iesire"<<endl;
                cout << "Introduceti optiuneaA: ";
                int optiuneA;
                cin >> optiuneA;

                if(optiuneA==1)
                {
                    try
                    {
                        magazin.adaugaAngajat();
                    }
                    catch (const exception& e)
                    {
                        cout << "Eroare: " << e.what() << endl;
                    }
                }
                else if(optiuneA==2)

                {
                    int id;
                    cout << "Introduceti ID-ul angajatului pe care doriti sa-l stergeti: ";
                    cin >> id;
                    magazin.stergeAngajat(id);
                    if(magazin.verifica()==0)
                    {
                        continuaA=0;
                        continua=0;
                    }
                }
                else if(optiuneA==3)
                {
                    try
                    {
                        int id;
                        string nouNume;
                        cout << "Introduceti ID-ul angajatului: ";
                        cin >> id;
                        cout << "Introduceti noul nume: ";
                        cin >> nouNume;

                        magazin.modificaNumeAngajat(id, nouNume);
                    }
                    catch (const exception& e)
                    {
                        cout << "Eroare: " << e.what() << endl;
                    }
                }
                else if(optiuneA==4)
                {
                    int id;
                    cout << "Introduceti ID-ul angajatului: ";
                    cin >> id;
                    magazin.afisareAngajat(id);
                }
                else if(optiuneA==5)
                    magazin.afisareAngajati();
                else if(optiuneA==0)
                    continuaA=0;
                else
                    cout<<"Optiune invalida. Incearca din nou!"<<endl;

                if (continuaA)
                {
                    cout << "Doriti sa continuati gestionarea angajatilor? (D/N): ";
                    char raspunsA;
                    cin >> raspunsA;
                    if (raspunsA == 'D' || raspunsA =='d')
                        continuaA=1;
                    else continuaA=0;
                }
            }
            while (continuaA);
        }
        else if (optiune == 2)
        {
            bool continuaB = true;
            do
            {
                cout << "MENIU GESTIONARE STOC"<<endl;
                cout << "1. Adauga produs de la tastatura"<<endl;
                cout << "2. Sterge un produs dupa cod"<<endl;
                cout << "3. Modifica numarul de produse din stoc-dupa cod"<<endl;
                cout << "4. Afiseaza datele unui produs dupa cod"<<endl;
                cout << "5. Afiseaza toate produsele"<<endl;
                cout << "0. Iesire"<<endl;
                cout << "Introduceti optiuneaB: ";
                int optiuneB;
                cin >> optiuneB;

                if(optiuneB==1)
                {
                    try
                    {
                        magazin.adaugaProdus();
                    }
                    catch (const exception& e)
                    {
                        cout << "Eroare: " << e.what() << endl;
                    }
                }
                else if(optiuneB==2)

                {
                    int cod;
                    cout << "Introduceti cod-ul produsului pe care doriti sa-l stergeti: ";
                    cin >> cod;
                    magazin.stergeProdus(cod);
                    if(magazin.verifica()==0)
                    {
                        continuaB=0;
                        continua=0;
                    }
                }
                else if(optiuneB==3)
                {
                    try
                    {
                        int cod;
                        int nounr;
                        cout << "Introduceti cod-ul produsului: ";
                        cin >> cod;
                        cout << "Introduceti noul numar de produse in stoc: ";
                        cin >> nounr;

                        magazin.modificaNrProduse(cod, nounr);
                    }
                    catch (const exception& e)
                    {
                        cout << "Eroare: " << e.what() << endl;
                    }
                }
                else if(optiuneB==4)
                {
                    int cod;
                    cout << "Introduceti cod-ul produsului: ";
                    cin >> cod;
                    magazin.afisareProdus(cod);
                }
                else if(optiuneB==5)
                    magazin.afisareProduse();
                else if(optiuneB==0)
                    continuaB=0;
                else
                    cout<<"Optiune invalida. Incearca din nou!"<<endl;

                if (continuaB)
                {
                    cout << "Doriti sa continuati gestionarea produselor? (D/N): ";
                    char raspunsB;
                    cin >> raspunsB;
                    if (raspunsB == 'D' || raspunsB =='d')
                        continuaB=1;
                    else continuaB=0;
                }
            }
            while (continuaB);
        }
        else if (optiune == 0)
            continua = 0;  // Ieșire din meniul principal
        else
        {
            cout << "Optiune invalida. Incearca din nou!" << endl;
        }
        if (continua)
        {
            cout << "Doriti sa mai selectati o optiune din meniul principal? (D/N): ";
            char raspuns;
            cin >> raspuns;
            if (raspuns == 'D' || raspuns =='d')
                continua=1;
            else continua=0;
        }
    }

    return 0;
}
