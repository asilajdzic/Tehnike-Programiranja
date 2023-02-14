//TP 2018/2019: Zadaća 5, Zadatak 4
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
class ApstraktnoVozilo
{
    int tezina;
public:
    ApstraktnoVozilo(int tezina): tezina(tezina) {}
    virtual ~ApstraktnoVozilo() {}
    virtual int DajTezinu()     const
    {
        return tezina;
    }
    virtual int DajUkupnuTezinu() const =0;
    virtual ApstraktnoVozilo* DajKopiju() const =0;
    virtual void IspisiPodatke()    const =0;
};
class Automobil: public ApstraktnoVozilo
{
    std::vector<int> v_tezina_putnika;
public:
    Automobil(int tezina, std::vector<int> v): ApstraktnoVozilo(tezina), v_tezina_putnika(v) {}
    int DajUkupnuTezinu()   const override
    {
        int suma=0;
        std::for_each(v_tezina_putnika.begin(),v_tezina_putnika.end(),[&suma](int n) {
            suma+=n;
        });
        return DajTezinu()+suma;
    }
    Automobil* DajKopiju() const override
    {
        return new Automobil(*this);
    }
    void IspisiPodatke()    const override
    {
        std::cout<<"Vrsta vozila: Automobil"<<std::endl
                 <<"Vlastita tezina: "<<DajTezinu()<<std::endl
                 <<"Tezina putnika: ";
        for(int i=0; i<v_tezina_putnika.size(); i++) {
            std::cout<<v_tezina_putnika.at(i);
            if(i!=v_tezina_putnika.size()-1) std::cout<<", ";
        }
        std::cout<<std::endl<<"Ukupna tezina: "<<DajUkupnuTezinu();
    }
};
class Kamion: public ApstraktnoVozilo
{
    int tezina_tereta;
public:
    Kamion(int tezina, int tezina_tereta): ApstraktnoVozilo(tezina), tezina_tereta(tezina_tereta) {}
    int DajUkupnuTezinu()   const override
    {
        return DajTezinu()+tezina_tereta;
    }
    Kamion* DajKopiju() const override
    {
        return new Kamion(*this);
    }
    void IspisiPodatke() const override
    {
        std::cout<<"Vrsta vozila: Kamion"<<std::endl
                 <<"Vlastita tezina: "<<DajTezinu()<<std::endl
                 <<"Tezina tereta: "<<DajUkupnuTezinu()-DajTezinu()<<std::endl
                 <<"Ukupna tezina: "<<DajUkupnuTezinu()<<std::endl;
    }
};
class Autobus: public ApstraktnoVozilo
{
    int broj_putnika;
    double prosjecna_tezina;
public:
    Autobus(int tezina, int broj_putnika, double prosjecna_tezina):
        ApstraktnoVozilo(tezina), broj_putnika(broj_putnika), prosjecna_tezina(prosjecna_tezina) {}
    int DajUkupnuTezinu()   const override
    {
        return DajTezinu()+broj_putnika*prosjecna_tezina;
    }
    Autobus* DajKopiju()    const override
    {
        return new Autobus(*this);
    }
    void IspisiPodatke()    const override
    {
        std::cout<<"Vrsta vozila: Autobus"<<std::endl
                 <<"Vlastita tezina: "<<DajTezinu()<<std::endl
                 <<"Broj putnika: "<<broj_putnika<<std::endl
                 <<"Prosjecna tezina putnika: "<<prosjecna_tezina<<std::endl
                 <<"Ukupna tezina: "<<DajUkupnuTezinu();
    }
};
class Vozilo
{
    ApstraktnoVozilo* vozilo;
public:
    Vozilo()
    {
        vozilo=nullptr;
    }
    Vozilo(const ApstraktnoVozilo &v)
    {
        vozilo=v.DajKopiju();
    }
    ~Vozilo()
    {
        delete vozilo;
    }
    Vozilo(Vozilo &&v)
    {
        vozilo=v.vozilo;
        v.vozilo=nullptr;
    }
    Vozilo(const Vozilo &v)
    {
        vozilo=v.vozilo->DajKopiju();
    }
    Vozilo &operator=(Vozilo &&v)
    {
        if(&v!=this) {
            delete vozilo;
            vozilo=v.vozilo;
            v.vozilo=nullptr;
        } else vozilo=nullptr;
        return *this;
    }
    Vozilo &operator= (const Vozilo &v)
    {
        if(&v!=this) {
            delete vozilo;
            vozilo=v.vozilo->DajKopiju();
        } else vozilo=nullptr;
        return *this;
    }
    int DajTezinu() const
    {
        if(!vozilo) throw std::logic_error("Nespicificirano vozilo");
        return vozilo->DajTezinu();
    }
    int DajUkupnuTezinu()   const
    {
        if(!vozilo) throw std::logic_error("Nespicificirano vozilo");
        return vozilo->DajUkupnuTezinu();
    }
    void IspisiPodatke()
    {
        if(!vozilo) throw std::logic_error("Nespicificirano vozilo");
        vozilo->IspisiPodatke();
    }
};
int main ()
{
    std::string dat;
    std::cin>>dat;
    std::ifstream ulaz(dat);
    if(!ulaz)   throw std::logic_error("Trazena datoteka ne postoji");
    std::vector<Vozilo> v;
    char znak;
    bool greska=false;
    while(ulaz>>znak) {
        if(znak=='A') {
            int tezina, broj_putnika;
            std::vector<int> tezine;
            ulaz>>tezina>>broj_putnika;
            for(int i=0; i<broj_putnika; i++) {
                int tezina_1_putnika;
                if(!(ulaz>>tezina_1_putnika))   greska=true;
                tezine.push_back(tezina_1_putnika);
            }
            v.push_back(Automobil(tezina, tezine));
        } else if(znak=='K') {
            int tezina, tezina_tereta;
            if(!(ulaz>>tezina>>tezina_tereta))  greska=true;
            v.push_back(Kamion(tezina, tezina_tereta));
        } else if(znak=='B') {
            int tezina, broj_putnika;
            double prosjecna_tezina;
            if(!(ulaz>>tezina>>broj_putnika>>prosjecna_tezina))
                greska=true;
            v.push_back(Autobus(tezina,broj_putnika,prosjecna_tezina));
        } else greska=true;
        if(greska)  break;
    }
    if(greska || ulaz.bad())
        throw std::logic_error("Problemi pri citanju");
    std::sort(v.begin(), v.end(), [] (const Vozilo &v1, const Vozilo &v2) {
        return v1.DajUkupnuTezinu()<v2.DajUkupnuTezinu();
    });
    for(auto x : v) {
        std::cout<<x.DajUkupnuTezinu()<<std::endl;
    }
    return 0;
}