//TP 2018/2019: Zadaća 5, Zadatak 3
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
class Narudzba
{
    const char *naziv_obroka, *narucioc;
    double cijena;
public:
    Narudzba(const char *naziv_obroka,  double cijena, const char *narucioc):
        naziv_obroka(naziv_obroka), narucioc(narucioc), cijena(cijena)  {}
    virtual ~Narudzba() {}
    std::string DajNazivObroka()    const
    {
        return naziv_obroka;
    }
    double DajCijenuObroka()  const
    {
        return cijena;
    }
    std::string DajNarucioca()  const
    {
        return narucioc;
    }
    virtual void Ispisi()   const
    {
        std::cout<<"Obrok: "<<DajNazivObroka()<<std::endl;
        std::cout<<"Cijena: "<<DajCijenuObroka()<<" KM"<<std::endl;
        std::cout<<"Narucilac: "<<DajNarucioca()<<std::endl;
    }
    virtual double DajUkupnuCijenu()    const
    {
        return cijena;
    }
    virtual Narudzba* DajKopiju()   const
    {
        return new Narudzba(*this);
    }
};
class NarudzbaSaPicem: public Narudzba
{
    const char* naziv_pica;
    double cijena_pica;
public:
    NarudzbaSaPicem(const char *naziv_obroka,  double cijena, const char *narucioc, const char *naziv_pica, double cijena_pica):
        Narudzba(naziv_obroka, cijena, narucioc), naziv_pica(naziv_pica), cijena_pica(cijena_pica)  {}
    ~NarudzbaSaPicem() {}
    std::string DajNazivPica()  const
    {
        return naziv_pica;
    }
    double DajCijenuPica()  const
    {
        return cijena_pica;
    }
    double DajUkupnuCijenu()    const override
    {
        return DajCijenuObroka()+DajCijenuPica();
    }
    void Ispisi()   const override
    {
        std::cout<<"Obrok: "<<DajNazivObroka()<<std::endl
                 <<"Pice: "<<DajNazivPica()<<std::endl
                 <<"Cijena: "<<DajCijenuObroka()<<" KM"<<std::endl
                 <<"Cijena pica: "<<DajCijenuPica()<<" KM"<<std::endl
                 <<"Ukupna cijena: "<<DajUkupnuCijenu()<<" KM"<<std::endl
                 <<"Narucilac: "<<DajNarucioca()<<std::endl;
    }
    NarudzbaSaPicem* DajKopiju() const override
    {
        return new NarudzbaSaPicem(*this);
    }
};
class Narudzbe
{
    std::vector<Narudzba*> v;
    double PronadjiCijenuPoNazivu(std::string dat,std::string naziv);
public:
    Narudzbe()=default;
    ~Narudzbe()
    {
        for(int i=0; i<v.size(); i++) delete v.at(i);
    }
    Narudzbe(const Narudzbe &n)
    {
        for(int i=0; i<n.v.size(); i++)
            v.push_back(n.v.at(i)->DajKopiju());
    }
    Narudzbe(Narudzbe &&n)
    {
        v=n.v;
        n.v.resize(0);
    }
    Narudzbe operator =(const Narudzbe &n);
    Narudzbe operator =(Narudzbe &&n);
    void NaruciObrok(const char *naziv_obroka, double cijena, const char *narucioc)
    {
        v.push_back(new Narudzba(naziv_obroka,cijena,narucioc));
    }
    void NaruciObrokSaPicem(const char *naziv_obroka, double cijena, const char *narucioc, const char *naziv_pica, double cijena_pica)
    {
        v.push_back(new NarudzbaSaPicem(naziv_obroka, cijena, narucioc, naziv_pica, cijena_pica));
    }
    void ObradiNarudzbu();
    bool DaLiImaNarudzbi()
    {
        return v.size();
    }
    int operator[](std::string narucioc)    const;
    void UcitajIzDatoteka(std::string ulaz1, std::string ulaz2);
};
Narudzbe Narudzbe::operator =(const Narudzbe &n)
{
    if(this==&n)    return *this;
    for(int i=0; i<v.size(); i++) delete v.at(i);
    v.resize(0);
    for(int i=0; i<n.v.size(); i++)
        v.push_back(n.v.at(i)->DajKopiju());
    return *this;
}
Narudzbe Narudzbe::operator =(Narudzbe &&n)
{
    if(this==&n)    return *this;
    for(int i=0; i<v.size(); i++) delete v.at(i);
    v.resize(0);
    v=n.v;
    n.v.resize(0);
    return *this;
}
void Narudzbe::ObradiNarudzbu()
{
    if(!DaLiImaNarudzbi())  throw std::range_error("Nema vise narudzbi");
    v.at(0)->Ispisi();
    delete v.at(0);
    v.erase(v.begin());
}
int Narudzbe::operator [](std::string narucioc) const
{
    int suma=0;
    for(int i=0; i<v.size(); i++)
        if(v.at(i)->DajNarucioca()==narucioc)
            suma+=v.at(i)->DajUkupnuCijenu();
    return suma;
}
void Narudzbe::UcitajIzDatoteka(std::string ul1, std::string ul2)
{
    std::ifstream ulaz(ul1);
    if(!ulaz)   throw   std::logic_error("Trazena datoteka ne postoji");
    std::string naziv_obroka,naziv_pica,narucioc;
    double cijena_obroka, cijena_pica;
    while(std::getline(ulaz, narucioc)) {
        std::getline(ulaz,naziv_obroka);
        //if(naziv_obroka.empty())    break;
        cijena_obroka=PronadjiCijenuPoNazivu(ul2,naziv_obroka);
        std::getline(ulaz,naziv_pica);
        if(!naziv_pica.empty()) {
            cijena_pica=PronadjiCijenuPoNazivu(ul2, naziv_pica);
            NaruciObrokSaPicem(naziv_obroka.c_str(), cijena_obroka, narucioc.c_str(), naziv_pica.c_str(), cijena_pica);
        } else NaruciObrok(naziv_obroka.c_str(), cijena_obroka, narucioc.c_str());
    }
    if(ulaz.fail() && !ulaz.eof())  throw std::logic_error("Problemi pri citanju");
}
double Narudzbe::PronadjiCijenuPoNazivu(std::string dat, std::string naziv)
{
    std::ifstream ulaz(dat);
    if(!ulaz)   throw   std::logic_error("Trazena datoteka ne postoji");
    std::string red;
    double cijena;
    while(std::getline(ulaz, red)) {
        if(red==naziv) {
            if(!(ulaz>>cijena)) throw std::logic_error("Problemi pri citanju");
            return cijena;
        }
    }
    if(ulaz.fail() && !ulaz.eof())  throw std::logic_error("Problemi pri citanju");
    throw std::logic_error("Nema odgovarajuce cijene");
}
int main ()
{
    
    return 0;
}