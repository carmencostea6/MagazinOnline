#include "Angajat.h"
using namespace std;


void Angajat::CNPvalid()
{
    if (CNP.size()!=13)
        throw invalid_argument("CNP-UL TREBUIE SA AIBA 13 CARACTERE");
    for(auto it=CNP.begin();it!=CNP.end();it++)
        if(!isdigit(*it))
            throw invalid_argument("Caracterele CNP-ului trebuie sa fie cifre");
    //verific validitatea CNP-ului cu datele de pe Wikipedia
    const int constanta[12] = {2,7,9,1,4,6,3,5,8,2,7,9};
    int suma =0;
    for (int i=0; i<12; i++)
        suma=suma+(CNP[i] -'0')*constanta[i];
    int rest =suma%11;
    int C;
    if (rest<10)
        C = rest;
    else
        C=1;
    if (C!=(CNP[12]-'0'))
        throw invalid_argument("CNP-ul nu este valid");
}
void Angajat::Numevalid()
{
    if(nume.size()<3 || nume.size()>30)
        throw invalid_argument("Numele trebuie sa aiba intre 3 si 30 de caractere");
    if(prenume.size()<3 || prenume.size()>30)
        throw invalid_argument("Prenumele trebuie sa aiba intre 3 si 30 de caractere");
}


int Angajat::getAniVechime() const
{
    int ziAngajare = stoi(dataAngajarii.substr(0, 2));
    int lunaAngajare = stoi(dataAngajarii.substr(3, 2));
    int anAngajare = stoi(dataAngajarii.substr(6, 4));

    //verific daca ziua si luna angajarii sunt corecte
    if (lunaAngajare < 1 || lunaAngajare > 12 || ziAngajare < 1 || ziAngajare > 31)
        throw invalid_argument("Data angajarii nu este valida.");

    //sursa:W3Schools
    time_t timestamp = time(nullptr);
    struct tm datetime = *localtime(&timestamp);
    int ziCurenta = datetime.tm_mday;
    int lunaCurenta = datetime.tm_mon + 1;
    int anCurent = datetime.tm_year + 1900;

    int aniVechime = anCurent - anAngajare;
    if (lunaAngajare > lunaCurenta || (lunaAngajare == lunaCurenta && ziAngajare > ziCurenta))
    {
        aniVechime--;
    }

    return aniVechime;
}


bool Angajat::esteZiuaAngajatului() const//ma intereseaza daca ziua angajatului este in luna curenta pentru a ii adauga 100 RON la salariu
{

    //int ziNastere=stoi(dataNastere.substr(0,2));
    int lunaNastere=stoi(CNP.substr(3,2));
    //sursa:W3Schools
    time_t timestamp = time(nullptr);
    struct tm datetime = *localtime(&timestamp);
    //int ziCurenta=datetime.tm_mday;
    int lunaCurenta=datetime.tm_mon+1;
    return(/*ziNastere==ziCurenta && */lunaNastere==lunaCurenta);

}

bool Angajat::esteMajor() const
{
    string an=CNP.substr(1,2);
    if (CNP[0]=='5' || CNP[0]=='6')
        an="20"+an;
    if (CNP[0]=='1' || CNP[0]=='2')
        an="19"+an;
    string luna=CNP.substr(3,2);
    string zi=CNP.substr(5,2);
    int   anNastere=stoi(an);
    int  lunaNastere=stoi(luna);
    int ziNastere=stoi(zi);

    //sursa:W3Schools
    time_t timestamp = time(nullptr);
    struct tm datetime = *localtime(&timestamp);
    int ziCurenta = datetime.tm_mday;
    int lunaCurenta = datetime.tm_mon + 1;
    int anCurent = datetime.tm_year + 1900;

    int varsta=anCurent-anNastere;
    if(lunaNastere>lunaCurenta ||(lunaNastere==lunaCurenta && ziNastere>ziCurenta))
        varsta--;
    return(varsta>=18);

}
void Angajat::setNume(string &numeNou)
{
    if(numeNou.size()<3 || numeNou.size()>30)
        throw invalid_argument("Numele nou trebuie sa aiba intre 3 si 30 de caractere");
    nume=numeNou;
}

