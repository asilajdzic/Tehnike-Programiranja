//TP 2018/2019: Tutorijal 8, Zadatak 3
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
const int BrojPredmeta=8;
struct Datum {
    int dan;
    int mjesec;
    int godina;
};
struct Ucenik {
    std::string ime,prezime;
    Datum datum_rodjenja;
    int ocjene[BrojPredmeta];
    double prosjek;
    bool prolaz;
};
int main ()
{
    void UnesiUcenike(Ucenik **p_ucenici, int brojUcenika);
    void ObradiUcenike(Ucenik **p_ucenici, int brojUcenika);
    void IspisiIzvjestaj(Ucenik **p_ucenici, int brojUcenika);
    void OslovodiMemoriju(Ucenik **p_ucenici, int brojUcenika);
    int brojUcenika;
    std::cout<<"Koliko ima ucenika: ";
    std::cin>>brojUcenika;
    try {
        Ucenik **p_ucenici=nullptr;
        p_ucenici=new Ucenik*[brojUcenika];
        try {
            UnesiUcenike(p_ucenici,brojUcenika);
        }
        catch(...) {
            OslovodiMemoriju(p_ucenici,brojUcenika);
            throw;
        }
        ObradiUcenike(p_ucenici, brojUcenika);
        IspisiIzvjestaj(p_ucenici, brojUcenika);
        OslovodiMemoriju(p_ucenici, brojUcenika);
    }
    catch(...) {
        std::cout<<"Problemi s memorijom...\n";
    }
	return 0;
}
void UnesiUcenike (Ucenik **p_ucenici, int brojUcenika)
{
   void UnesiJednogUcenika(Ucenik *p_ucenik);
   for(int i=0;i<brojUcenika;i++)
   {
       p_ucenici[i]=nullptr;
       std::cout<<"Unesite podatke za "<<i+1<<". ucenika:\n";
       p_ucenici[i]=new Ucenik;
       UnesiJednogUcenika(p_ucenici[i]);
   }
    
}
void UnesiJednogUcenika(Ucenik *p_ucenik)
{
    void UnesiDatum(Datum &datum);
    void UnesiOcjene(int ocjene[], int BrojPredmeta);
    std::cout<<"  Ime: ";
    std::cin>>p_ucenik->ime;
    std::cout<<"  Prezime: ";
    std::cin>>p_ucenik->prezime;
    std::cout<<"  Datum rodjenja (D/M/G): ";
    UnesiDatum(p_ucenik->datum_rodjenja);
    UnesiOcjene(p_ucenik->ocjene,BrojPredmeta);
}
void UnesiDatum (Datum &datum)
{
    char znak;
    std::cin>>datum.dan>>znak>>datum.mjesec>>znak>>datum.godina;
}
void UnesiOcjene(int ocjene[], int BrojPredmeta)
{
    for(int i=0;i<BrojPredmeta;i++){
    std::cout<<"  Ocjena iz "<<i+1<<". predmeta: ";
    std::cin>>ocjene[i];
    }
}
void ObradiUcenike(Ucenik **p_ucenici, int brojUcenika) 
{
    void ObradiJednogUcenika(Ucenik *p_ucenik);
    for(int i=0;i<brojUcenika;i++)
        ObradiJednogUcenika(p_ucenici[i]);
    std::sort(p_ucenici,p_ucenici+brojUcenika,[](const Ucenik *ucenik1, const Ucenik *ucenik2)
    {
        return ucenik1->prosjek>ucenik2->prosjek;
    });
}
void ObradiJednogUcenika(Ucenik *p_ucenik)
{
    double suma=0;
    p_ucenik->prosjek=1;
    p_ucenik->prolaz=false;
    for(int ocjena : p_ucenik->ocjene)
    {
     if(ocjena==1) return;
     suma+=ocjena;
    }
    p_ucenik->prolaz=true;
    p_ucenik->prosjek=suma/BrojPredmeta;
}
void IspisiIzvjestaj(Ucenik **p_ucenici, int brojUcenika)
{
    void IspisiJednogUcenika(Ucenik *p_ucenik);
    std::cout<<"\n";
    for(int i=0;i<brojUcenika;i++)
    IspisiJednogUcenika(p_ucenici[i]);
}
void IspisiJednogUcenika(Ucenik *p_ucenik)
{
    void IspisiDatum(const Datum &datum);
    std::cout<<"Ucenik "<<p_ucenik->ime<<" "<<p_ucenik->prezime<<" rodjen ";
    IspisiDatum(p_ucenik->datum_rodjenja);
    if(p_ucenik->prolaz)
        std::cout<<" ima prosjek "<<std::setprecision(3)<<p_ucenik->prosjek<<"\n";
    else
        std::cout<<" mora ponavljati razred\n";
}
void IspisiDatum(const Datum &datum)
{
    std::cout<<datum.dan<<"/"<<datum.mjesec<<"/"<<datum.godina;
}
void OslovodiMemoriju(Ucenik** p_ucenici, int brojUcenika)
{
    for(int i=0;i<brojUcenika;i++)
    delete p_ucenici[i];
    delete[] p_ucenici;
}