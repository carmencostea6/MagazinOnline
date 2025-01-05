#include "Magazin.h"
using namespace std;
//Verific daca exista deja ID ul dat in vectorul meu de angajati
bool Magazin::idUnic(int id)
{
    return none_of(angajati.begin(), angajati.end(),[id](Angajat* angajat) //expresie lambda-returneaza 1 daca nici un Angajat nu are id-ul cautat
    {
        return angajat->getID() == id;
    });
}
//IMPLEMENTARE TASK 1

void Magazin::citesteAngajati(ifstream& f)
{
    int id;
    string tip, nume, prenume, cnp, data;
    while (f>>tip >>id >>nume>> prenume>>cnp>> data)
    {
        try
        {
            if (!idUnic(id))
                throw invalid_argument("ID-ul exista deja");
            Angajat* angajat = nullptr;
            if (tip == "Manager")
            {
                angajat = new Manager(id, nume, prenume, cnp, data);
                nrManageri++;
            }
            else if (tip == "Operator")
            {
                angajat = new Operator_Comenzi(id, nume, prenume, cnp, data);
                nrOperatori++;
            }
            else if (tip == "Asistent")
            {
                angajat = new Asistent(id, nume, prenume, cnp, data);
                nrAsistenti++;
            }
            else
                 throw invalid_argument("Tip de angajat necunoscut.");
            angajati.push_back(angajat);
        }
        catch (const exception& e)
        {
            cout<< "Eroare: " << e.what() << endl;
            f.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoră restul liniei
        }
    }
}


void Magazin::adaugaAngajat()
{
    bool ok=0;
    do
    {
        try
        {
            int id;
            string nume,prenume,cnp,tip;
            cout<<"Introdu id-ul persoanei:"<<endl;
            cin>>id;
            if(!idUnic(id))
                throw invalid_argument("ID-ul dat exista deja");
            cout<<"Introdu postul pe care se angajeaza persoana:"<<endl;
            cin>>tip;
            cout<<"Introdu numele persoanei"<<endl;
            cin>>nume;
            cout<<"Introdu prenumele persoanei"<<endl;
            cin>>prenume;
            cout<<"Introdu CNP-ul persoanei:"<<endl;
            cin>>cnp;
            //persoana Angajata va primii data angajarii data curenta
            time_t timestamp = time(nullptr);
            struct tm datetime = *localtime(&timestamp);
            int ziCurenta = datetime.tm_mday;
            int lunaCurenta = datetime.tm_mon + 1;
            int anCurent = datetime.tm_year + 1900;
            string zi,luna;
            if(ziCurenta<=9)
                zi="0"+to_string(ziCurenta);
            else
                zi=to_string(ziCurenta);
            if(lunaCurenta<=9)
                luna="0"+to_string(lunaCurenta);
            else
                luna=to_string(lunaCurenta);
            string an=to_string(anCurent);
            string data=zi+"/"+luna+"/"+an;

            Angajat *angajat=nullptr;
            if(tip=="Manager")
            {
                angajat=new Manager(id,nume,prenume,cnp,data);
                nrManageri++;
            }
            else if (tip=="Operator")
            {
                angajat=new Operator_Comenzi(id,nume,prenume,cnp,data);
                nrOperatori++;
            }
            else if (tip=="Asistent")
            {
                angajat=new Asistent(id,nume,prenume,cnp,data);
                nrAsistenti++;
            }
            else
                throw invalid_argument("Nu este cunoscut acest tip de angajat");
            angajati.push_back(angajat);
            ok=1;
            cout<<"Persoana a fost angajata cu succes!"<<endl;
        }
        catch(const exception &e)
        {
            cout<<e.what()<<endl;
            cout<<"Introduceti alte date pentru angajat :"<<endl;
        }

    }
    while(!ok);

}

void Magazin::stergeAngajat(int id)
{
    auto it = find_if(angajati.begin(), angajati.end(), [id](Angajat* angajat)
    {
        return angajat->getID() == id;
    });

    if (it != angajati.end())
    {
        if (dynamic_cast<Manager*>(*it))
            nrManageri--;
        else if (dynamic_cast<Operator_Comenzi*>(*it))
            nrOperatori--;
        else if (dynamic_cast<Asistent*>(*it))
            nrAsistenti--;
        delete (*it); // Eliberez memoria alocată dinamic
        angajati.erase(it); // Elimin elementul din vector
        cout << "Angajatul cu ID-ul " << id << " a fost eliminat" << endl;
    }
    else
        cout << "Eroare: Angajatul cu ID-ul " << id << " nu a fost găsit" << endl;
}

void Magazin::modificaNumeAngajat(int id, string& nouNume)
{
    auto it = find_if(angajati.begin(), angajati.end(),[id](Angajat* angajat) //expresie lambda-returneaza pozitia-un iterator- pe care se gaseste Angajatul cu id-ul cautat
    {
        return angajat->getID() == id;
    });

    if (it != angajati.end())
    {
        (*it)->setNume(nouNume);
        cout << "Numele angajatului cu ID-ul " << id << " a fost modificat in " << nouNume << endl;
    }
    else
        cout << "Eroare: Angajatul cu ID-ul " << id << " nu a fost gasit"<<endl;

}

void Magazin::afisareAngajat(int id) const
{
    auto it = find_if(angajati.begin(), angajati.end(),[id](Angajat* angajat)
    {
        return angajat->getID() == id;
    });

    if (it != angajati.end())
        (*it)->afisare();
    else
        cout << "Eroare: Angajatul cu ID-ul " << id << " nu a fost gasit"<<endl;
}

void Magazin::afisareAngajati() const
{

    for (auto it=angajati.begin(); it!=angajati.end(); it++)
        (*it)->afisare();

}

//IMPLEMENTARE TASK 2
void Magazin::citesteProduse(istream &g)
{
    string tip;
    while (g >> tip)
    {
        try
        {
            if (tip == "Haine")
            {
                nrHaine++;
                string denumire, data, culoare, marca;
                int nr;
                double pret;
                g>>denumire>>data>>nr>>pret>>culoare>>marca;
                produse.push_back(new Articole_Vestimentare(denumire, data, nr, pret, culoare, marca));
            }
            else if (tip == "Discuri")
            {
                nrDiscuri++;
                string denumire, data, casa, dataExp, trupa, numeA;
                int nr;
                double pret;
                g>>denumire>>data>>nr>>pret>>casa>>dataExp>>trupa>>numeA;
                produse.push_back(new Discuri(denumire, data, nr, pret, casa, dataExp, trupa, numeA));
            }
            else if (tip == "Vintage")
            {
                nrVintage++;
                string denumire, data;
                int nr, rar;
                double pret;
                bool mint;
                g>>denumire>>data>>nr>>pret>>mint>>rar;
                produse.push_back(new Discuri_Vintage(denumire, data, nr, pret, mint, rar));
            }
            else
            {
                cout<<"Tip necunoscut: "<<tip<<" Linia a fost ignorata!"<< endl;
                // Citire și ignorare restul liniei
                g.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        catch (const exception& e)
        {
            cout<<"Eroare: "<<e.what()<<endl;
            // Citire și ignorare restul liniei
            g.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


void Magazin::adaugaProdus()
{
    bool ok = 0;
    do
    {
        try
        {
            string tip, denumire, culoare, marca, casa, data_exp, trupa, numeA;
            int nr, rar;
            double pret;
            bool mint;

            cout << "Introdu tipul produsului (Haine / Discuri / Vintage): "<<endl;
            cin >> tip;
            cout << "Introdu denumirea produsului: "<<endl;
            cin >> denumire;
            cout << "Introdu numarul de produse: "<<endl;
            cin >> nr;
            cout << "Introdu pretul de baza: "<<endl;
            cin >> pret;

            // Produsul nou adaugat va avea data adaugarii pe stoc=data curenta
            time_t timestamp = time(nullptr);
            struct tm datetime = *localtime(&timestamp);
            int ziCurenta = datetime.tm_mday;
            int lunaCurenta = datetime.tm_mon + 1;
            int anCurent = datetime.tm_year + 1900;
            string zi,luna;
            if(ziCurenta<=9)
                zi="0"+to_string(ziCurenta);
            else
                zi=to_string(ziCurenta);
            if(lunaCurenta<=9)
                luna="0"+to_string(lunaCurenta);
            else
                luna=to_string(lunaCurenta);
            string an=to_string(anCurent);
            string data=zi+"/"+luna+"/"+an;
            Produs* produs = nullptr;

            if (tip == "Haine")
            {
                cout << "Introdu culoarea produsului: "<<endl;
                cin >> culoare;
                cout << "Introdu marca produsului: "<<endl;
                cin >> marca;
                nrHaine++;
                produs = new Articole_Vestimentare(denumire, data, nr, pret, culoare, marca);
            }
            else if (tip == "Discuri")
            {
                cout << "Introdu casa de discuri: "<<endl;
                cin >> casa;
                cout << "Introdu data punerii in vanzare: "<<endl;
                cin >> data_exp;
                cout << "Introdu trupa: "<<endl;
                cin >> trupa;
                cout << "Introdu numele albumului: "<<endl;
                cin >> numeA;
                nrDiscuri++;
                produs = new Discuri(denumire, data, nr, pret, casa, data_exp, trupa, numeA);
            }
            else if (tip == "Vintage")
            {
                cout << "Produsul este folosit?"<<endl;
                cin >> mint;
                cout << "Introdu coeficientul de raritate (1-5): "<<endl;
                cin >> rar;
                nrVintage++;
                produs = new Discuri_Vintage(denumire, data, nr, pret, mint, rar);
            }
            else
            {
                throw invalid_argument("Tipul de produs este necunoscut.");
            }

            produse.push_back(produs);
            ok = 1;
            cout << "Produsul a fost adaugat cu succes!" << endl;
        }
        catch (const exception& e)
        {
            cout << e.what() << endl;
            cout << "Introduceti alte date pentru produs." << endl;
        }
    }
    while (!ok);
}



void Magazin::stergeProdus(int cod)
{
    auto it = find_if(produse.begin(), produse.end(), [cod](Produs* produs)
    {
        return produs->getCod() == cod;
    });

    if (it != produse.end())
    {
        if (dynamic_cast<Articole_Vestimentare*>(*it))
            nrHaine--;
        else if (dynamic_cast<Discuri*>(*it))
            nrDiscuri--;
        else if (dynamic_cast<Discuri_Vintage*>(*it))
            nrVintage--;
        delete (*it); // Eliberez memoria alocată dinamic
        produse.erase(it); // Elimin elementul din vector
        cout << "Produsul cu cod-ul " << cod << " a fost eliminat" << endl;
    }
    else
        cout << "Eroare: Produsul cu cod-ul " << cod << " nu a fost găsit" << endl;
}

void Magazin::modificaNrProduse(int cod, int nr)
{
    auto it = find_if(produse.begin(), produse.end(),[cod](Produs* produs)
    {
        return produs->getCod() == cod;
    });

    if (it != produse.end())
    {
        (*it)->setNrProd(nr);
        cout << "Numarul de produse din stoc cu cod-ul " << cod << " a fost modificat in " << nr << endl;
    }
    else
        cout << "Eroare: Produsul cu cod-ul " << cod << " nu a fost gasit"<<endl;
}

void Magazin::afisareProdus(int cod) const
{
    auto it = find_if(produse.begin(), produse.end(),[cod](Produs* produs)
    {
        return produs->getCod() == cod;
    });

    if (it != produse.end())
        (*it)->afisare();
    else
        cout << "Eroare: Produsul cu cod-ul " << cod << " nu a fost gasit"<<endl;
}

void Magazin::afisareProduse()const
{
    for (auto it=produse.begin(); it!=produse.end(); it++)
        (*it)->afisare();
}

bool Magazin::verifica() const
{
    if (nrManageri < 1)
    {
        cout <<"Magazin indisponibil-Nu exista suficienti manageri!"<< endl;
        return 0;
    }
    if (nrOperatori < 3)
    {
        cout <<"Magazin indisponibil-Nu exista suficienti operatori de comenzi!"<< endl;
        return 0;
    }
    if (nrAsistenti < 1)
    {
        cout << "Magazin indisponibil-Nu exista suficienti asistenti!" << endl;
        return 0;
    }
    if (nrHaine < 2)
    {
        cout <<"Magazin indisponibil-Nu exista suficiente articole vestimentare!"<< endl;
        return 0;
    }
    if (nrDiscuri < 2)
    {
        cout <<"Magazin indisponibil-Nu exista suficiente discuri!"<< endl;
        return 0;
    }
    if (nrVintage < 2)
    {
        cout << "Magazin indisponibil-Nu exista suficiente discuri vintage!" << endl;
        return 0;
    }

    cout << "Magazin disponibil - Toate conditiile sunt indeplinite." << endl;
    return 1;
}

Magazin::~Magazin()
{
    for (auto it=angajati.begin(); it!=angajati.end(); it++)
        delete (*it);  // Eliberez memoria alocata dinamic pentru fiecare angajat
    angajati.clear();  // Golesc vectorul de angajati

    for (auto it = produse.begin(); it != produse.end(); it++)
        delete (*it);  // Eliberez memoria alocata dinamic pentru fiecare produs
    produse.clear();  // Golesc vectorul de produse
}
