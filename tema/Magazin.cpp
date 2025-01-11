#include "Magazin.h"
using namespace std;
string Magazin::getDataCurenta()
{
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
    return data;
}
//TASK 1
//Verific daca exista deja ID ul dat in vectorul meu de angajati
bool Magazin::idUnic(int id)
{
    return none_of(angajati.begin(), angajati.end(),[id](Angajat* angajat) //expresie lambda-returneaza 1 daca nici un Angajat nu are id-ul cautat
    {
        return angajat->getID() == id;
    });
}

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
            f.ignore(numeric_limits<streamsize>::max(), '\n'); //ignor restul liniei
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
            string data=getDataCurenta();//data angajarii va fi data curenta

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
        delete (*it);
        angajati.erase(it);
        cout << "Angajatul cu ID-ul " << id << " a fost eliminat" << endl;
    }
    else
        cout << "Eroare: Angajatul cu ID-ul " << id << " nu a fost gasit" << endl;
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

//TASK 2
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
                g.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        catch (const exception& e)
        {
            cout<<"Eroare: "<<e.what()<<endl;
            g.ignore(numeric_limits<streamsize>::max(), '\n');//ignora restul liniei
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
            string data=getDataCurenta();// Produsul nou adaugat va avea data adaugarii pe stoc=data curenta
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
                throw invalid_argument("Tipul de produs este necunoscut");
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
        delete (*it);
        produse.erase(it);
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
//TASK 3

Produs* Magazin::cautaProdus(int cod)
{
    for (auto it=produse.begin(); it!=produse.end(); it++)
        if((*it)->getCod()==cod)
            return (*it);
    cout<<"Produsul cu codul "<<cod<< " nu a fost gasit!"<<endl;
    return nullptr;
    if (produse.empty())
    {
        cout << "Nu exista produse in stoc!" << endl;
        return nullptr;
    }
}

Angajat* Magazin::cautaOperator()
{
    Operator_Comenzi* celMaiLiber = nullptr;
    int minComenzi = 1000;
    for (auto it=angajati.begin(); it!=angajati.end(); it++)
    {
        Operator_Comenzi* op=dynamic_cast<Operator_Comenzi*>(*it);
        if (op && op->esteDisponibil())
        {
            int nrComenzi = op->getNrComenziActive();
            if (nrComenzi < minComenzi)
            {
                celMaiLiber = op;
                minComenzi = nrComenzi;
            }
        }
    }
    if (!celMaiLiber)
        cout << "Nu exista operatori disponibili in acest moment" << endl;
    return celMaiLiber;
}

bool Magazin::validareComanda(const vector<shared_ptr<Produs>>& produseComandate, const vector<int>& cantitati) const
{
    int totalHaine = 0;
    int totalDiscuri = 0;
    for (int i = 0; i < produseComandate.size(); ++i)
    {
        auto produs = produseComandate[i];
        int cantitate = cantitati[i];
        if (dynamic_cast<const Articole_Vestimentare*>(produs.get()))
        {
            totalHaine += cantitate;
            if (totalHaine > 3)
            {
                throw invalid_argument ("Comanda depaseste limita de 3 articole vestimentare");
                return 0;
            }
        }
        else if (dynamic_cast<const Discuri*>(produs.get()) || dynamic_cast<const Discuri_Vintage*>(produs.get()))
        {
            totalDiscuri += cantitate;
            if (totalDiscuri > 5)
            {
                throw invalid_argument( "Comanda depaseste limita de 5 discuri");
                return 0;
            }
        }
        auto it = find_if(produse.begin(), produse.end(), [produs](Produs* p)
        {
            return p->getCod() == produs->getCod();
        });

        if (it == produse.end() || (*it)->getNrProd() < cantitate)
        {
            throw invalid_argument("Nu exista suficiente produse cu acest cod in stoc");
            return 0;
        }
    }

    double valoareTotala = 0;
    for (int i=0; i < produseComandate.size(); i++)
        valoareTotala += produseComandate[i]->getPretBaza() * cantitati[i];
    if (valoareTotala < 100.0)
    {
        throw invalid_argument("Valoarea comenzii (din  preturi de baza) trebuie sa fie de cel putin 100 RON");
        return 0;
    }
    return 1;
}

bool Magazin::actualizeazaStoc(const vector<shared_ptr<Produs>>& produseComandate, const vector<int>& cantitati)
{
    for (int i=0; i<produseComandate.size(); i++)
    {
        auto produs=produseComandate[i];
        int cantitate=cantitati[i];
        auto it = find_if(produse.begin(), produse.end(), [produs](Produs* p)
        {
            return p->getCod() ==produs->getCod();
        });
        if (it!=produse.end())
        {
            int NrProdRamase =(*it)->getNrProd()-cantitate;
            (*it)->setNrProd(NrProdRamase);
        }
        else
            return 0;
    }
    return 1;
}

void Magazin::citesteComenzi(ifstream &h)
{
    while (!comenzi.empty())
        comenzi.pop();
    while (!h.eof())
    {
        try
        {
            int durata;
            h >> durata;
            vector<shared_ptr<Produs>> produseComandate;
            vector<int> cantitati;
            while (true)
            {
                int cod, cantitate;
                h >> cod >> cantitate;
                Produs* produs = cautaProdus(cod);
                if (!produs)
                    throw invalid_argument("Nu exista in stoc produse cu acest cod");
                produseComandate.push_back(shared_ptr<Produs>(produs, [](Produs*) {}));
                cantitati.push_back(cantitate);
                if (h.peek() == '\n' || h.eof()) break;
            }
            string data=getDataCurenta();//data plasarii comenzii va fi data curenta
            // Validarea și adăugarea comenzii
            if (validareComanda(produseComandate, cantitati))
            {
                actualizeazaStoc(produseComandate, cantitati);
                adaugaComanda(produseComandate,cantitati, durata, data);
            }
            else
                cout << "Eroare: Comanda nu a fost validata." << endl;
        }
        catch (const exception& e)
        {
            cout << "Eroare la procesarea comenzii: " << e.what() << endl;
            h.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignor restul liniei
        }
    }

}

void Magazin::adaugaComanda(const vector<shared_ptr<Produs>>& produseComandate, const vector<int>& cantitati, int durata, const string& dataComenzii)
{
    // Validarea comenzii
    if (!validareComanda(produseComandate, cantitati))
        throw invalid_argument("Produsele comandate nu sunt disponibile sau cantitațile sunt insuficiente");
    // Actualizarea stocului
    if (!actualizeazaStoc(produseComandate, cantitati))
        throw invalid_argument("Eroare la actualizarea stocului");
    // Calcularea valorii totale a comenzii
    double valoare=0;
    double valoareTotala = 0;
    for (int i = 0; i < produseComandate.size(); i++)
    {
        valoare += produseComandate[i]->getPretBaza() * cantitati[i];
        valoareTotala+= produseComandate[i]->getPret() * cantitati[i];
    }
    if (valoare < 100.0)
        throw invalid_argument("Valoarea comenzii(din preturi de baza)trebuie sa fie de cel putin 100 RON");
    // Crearea unei noi comenzi ca shared_ptr
    auto comanda = make_shared<Comenzi>(dataComenzii, durata, produseComandate, valoareTotala);
    // Asignarea comenzii unui operator disponibil
    Angajat* operatorDisponibil = cautaOperator();
    if (operatorDisponibil)
    {
        auto* op = dynamic_cast<Operator_Comenzi*>(operatorDisponibil);
        op->adaugaComanda(comanda);
    }
    else
    {
        comenziAsteptare.push(comanda);
        cout << "Toti operatorii sunt ocupati si comanda a fost plasata in coada de asteptare" << endl;
    }
}

void Magazin::comenziInAsteptare()
{
    while (!comenziAsteptare.empty())
    {
        Angajat* operatorDisponibil = cautaOperator();
        if (!operatorDisponibil)
        {
            //cout << "Nu exista operatori disponibili." << endl;
            break;
        }
        auto comanda = comenziAsteptare.front();
        comenziAsteptare.pop();
        auto* op = dynamic_cast<Operator_Comenzi*>(operatorDisponibil);
        op->adaugaComanda(comanda);
    }
}

void Magazin::procesare()
{
    if (alldone)
    {
        cout << "Toate comenzile au fost deja procesate!"<<endl;
        return;
    }
    while (true)
    {
        bool comenziInProcesare = 0;
        cout << "_____________________________________________________\n";
        for (auto it = angajati.begin(); it != angajati.end(); ++it)
        {
            Operator_Comenzi* op = dynamic_cast<Operator_Comenzi*>(*it);
            if (op)
            {
                auto& comenziActive = op->getComenziActive();
                if (!comenziActive.empty())
                {
                    comenziInProcesare = 1;
                    cout << "Operatorul cu ID " << op->getID() << " proceseaza urmatoarele comenzi:" << endl;
                    int nrComenzi = comenziActive.size();
                    for (int i = 0; i < nrComenzi; ++i)
                    {
                        auto comanda = comenziActive.front();
                        comenziActive.pop();
                        cout << "  - Comanda cu ID " << comanda->getID() << ", incarcata la data: " << comanda->getData()<< ", in valoare de: " << comanda->getValoare() << ", durata de procesare: " << comanda->getDurata() << endl;
                        comanda->decrementDurataRamasa();
                        cout << "Durata ramasa: " << comanda->getDurataRamasa() << endl;
                        if (!comanda->esteFinalizata())
                            comenziActive.push(comanda);
                        else
                        {
                            cout << "!Comanda cu ID " << comanda->getID() << " a fost finalizata!" << endl;
                            op->adaugaComandaFinalizata(comanda);
                        }
                    }
                }
            }
        }
        comenziInAsteptare();
        if (!comenziInProcesare && comenziAsteptare.empty())
        {
            cout << "Toate comenzile au fost procesate" << endl;
            alldone=1;
            break;
        }

        this_thread::sleep_for(chrono::seconds(1));
    }
}
//Task 4
void Magazin::celeMaiMulteComenzi(ofstream &o1)
{
    int max=0;
    Operator_Comenzi * best=nullptr;
    for (auto it=angajati.begin(); it!=angajati.end(); it++)
    {
        auto* op=dynamic_cast<Operator_Comenzi*>(*it);
        if (op && op->getNrComenziProcesate() > max)
        {
            max=op->getNrComenziProcesate();
            best=op;
        }
    }
    if(best)
        o1<<"Angajatul:"<<best->getNume()<<" "<<best->getPrenume()<<" , cu ID-ul:"<< best->getID() <<" are cele mai multe comenzi procesate:"<< best->getNrComenziProcesate()<<endl;
}

void Magazin::celeMaiValoroaseComenzi(ofstream& o2)
{
    vector<pair<double, Operator_Comenzi*>> comenziValoroase; // Vector pentru a păstra valoarea și operatorul
    for (auto it = angajati.begin(); it != angajati.end(); it++)
    {
        auto* op = dynamic_cast<Operator_Comenzi*>(*it);
        if (op)
        {
            for (const auto& comanda : op->getComenziFinalizate())
            {
                comenziValoroase.emplace_back(comanda->getValoare(), op);
            }
        }
    }
    // Sortez descrescator dupa valoarea comenzii
    sort(comenziValoroase.begin(), comenziValoroase.end(), [](const auto& a, const auto& b)
    {
        return a.first > b.first;
    });
    // Scriu top 3 angajati care proceseaza cele mai val comenzi
    for (int i = 0; i < 3 && i < comenziValoroase.size(); ++i)
    {
        auto valoare = comenziValoroase[i].first;
        auto operatorul = comenziValoroase[i].second;
        o2 << " Operator: " << operatorul->getNume()<<" "<<operatorul->getPrenume()<< ", ID: " << operatorul->getID()<< ", Valoare comanda: " << valoare << " RON"<<endl;
    }
}

void Magazin::celMaiMareSalariu(ofstream &o3)
{
    vector<Angajat*> aux = angajati;
    // Sortez descrescator dupa nume și prenume
    sort(aux.begin(), aux.end(), [](Angajat* a, Angajat* b)
    {
        if (a->getSalariu() != b->getSalariu())
            return a->getSalariu() > b->getSalariu();
        if (a->getNume() != b->getNume())
            return a->getNume() < b->getNume();
        return a->getPrenume() < b->getPrenume();
    });
    for (int i = 0; i < 3; ++i)
    {
        auto* angajat = aux[i];
        o3<< " Angajat: " << angajat->getNume()<<" "<<angajat->getPrenume()<< ", ID: " << angajat->getID()<< ", salariu: " << angajat->getSalariu()<<endl;
    }

}


Magazin::~Magazin()
{
    for (auto it=angajati.begin(); it!=angajati.end(); it++)
        delete (*it);
    angajati.clear();
    for (auto it = produse.begin(); it != produse.end(); it++)
        delete (*it);
    produse.clear();
}
