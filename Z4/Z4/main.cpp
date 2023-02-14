//TP 2018/2019: Zadaća 4, Zadatak 4
#include <iostream>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <memory>
class Let
{
    static constexpr int vel_naziv_odredista=30;
    static constexpr int vel_oznaka_leta=10;
    char odrediste[vel_naziv_odredista];
    char oznaka_leta[vel_oznaka_leta];
    int kapija;
    int sat_polaska;
    int minute_polaska;
    int trajanje_leta;
    int kasni=0;
public:
    Let(const char odrediste[], const char oznaka_leta[], int kapija, int sat_polaska, int minute_polaska, int trajanje_leta);
    void PostaviKasnjenje(int kasnjenje)
    {
        kasni=kasnjenje;
    }
    bool DaLiKasni() const
    {
        return kasni;
    }
    int DajTrajanjeLeta() const
    {
        return trajanje_leta;
    }
    std::pair<int, int> DajOcekivanoVrijemePolijetanja() const
    {
        int minute=minute_polaska+kasni;
        int sati=sat_polaska+minute/60;
        sati%=24;
        minute%=60;
        return {sati,minute};
    }
    std::pair<int, int> DajOcekivanoVrijemeSlijetanja() const
    {
        int minute=minute_polaska+trajanje_leta+kasni;
        int sati=sat_polaska+minute/60;
        sati%=24;
        minute%=60;
        return {sati, minute};
    }
    void Ispisi() const; //fali
};
Let::Let(const char odrediste[], const char oznaka_leta[], int kapija, int sat_polaska, int minute_polaska, int trajanje_leta)
{
    if(strlen(odrediste)>vel_naziv_odredista)   throw std::domain_error("Predug naziv odredista");
    if(strlen(oznaka_leta)>vel_oznaka_leta) throw std::domain_error("Predug naziv oznake leta");
    if(sat_polaska<0) throw std::domain_error("Napravilni sati polaska");
    if(minute_polaska<0) throw std::domain_error("Napravilne minute polaska");
    strcpy(Let::oznaka_leta,oznaka_leta);
    strcpy(Let::odrediste,odrediste);
    Let::kapija=kapija;
    Let::sat_polaska=sat_polaska;
    Let::minute_polaska=minute_polaska;
    Let::trajanje_leta=trajanje_leta;
}
void Let::Ispisi() const
{
    std::cout<<std::setfill(' ')<<std::left<<std::setw(10)<<oznaka_leta;
    for(int i=0; i<20; i++) {
        if(i<strlen(odrediste))
            std::cout<<odrediste[i];
        else
            std::cout<<" ";
    }
    if(!DaLiKasni()) {
        std::cout<<std::right<<std::setw(3)<<" "<<std::setw(2)<<std::setfill('0')<<sat_polaska
                 <<":"<<std::setw(2)<<std::setfill('0')<<minute_polaska<<std::setw(3)<<std::setfill(' ')<<" "
                 <<std::setw(2)<<std::setfill('0')<<DajOcekivanoVrijemeSlijetanja().first
                 <<":"<<std::setw(2)<<std::setfill('0')<<DajOcekivanoVrijemeSlijetanja().second;
        std::cout<<std::right<<std::setw(6)<<std::setfill(' ')<<kapija;
    } else {
        std::cout<<std::right<<std::setw(3)<<" "<<std::setw(2)<<std::setfill('0')<<DajOcekivanoVrijemePolijetanja().first<<":"<<std::setw(2)<<std::setfill('0')<<DajOcekivanoVrijemePolijetanja().second;
        std::cout<<" (Planirano "<<std::setw(2)<<std::setfill('0')<<sat_polaska<<":"<<std::setw(2)<<std::setfill('0')<<minute_polaska<<", Kasni "<<kasni<<" min)";
    }
    std::cout<<std::endl;
}
class Letovi
{
    std::vector<std::shared_ptr<Let>> letovi;
public:
    explicit Letovi() {}
    Letovi(std::initializer_list<Let> lista_letova);
    Letovi(const Letovi &letovi);
    Letovi(Letovi &&letovi);
    Letovi &operator =(const Letovi &l)
    {
        letovi.resize(l.letovi.size());
        for(int i=0; i<l.letovi.size(); i++)
            letovi[i]=std::make_shared<Let>(*l.letovi[i]);
        return *this;
    }
    Letovi &operator =(Letovi &&l)
    {
        std::swap(letovi,l.letovi);
        return *this;
    }
    Let &DajPrviLet() const
    {
        auto izlaz=*std::min_element(letovi.begin(),letovi.end(),[](const std::shared_ptr<Let> &let1, const std::shared_ptr<Let> &let2) {
            return (let1->DajOcekivanoVrijemePolijetanja().first*60+let1->DajOcekivanoVrijemePolijetanja().second)
                   <(let2->DajOcekivanoVrijemePolijetanja().first*60+let2->DajOcekivanoVrijemePolijetanja().second);
        });
        return *izlaz;
    }
    Let &DajPosljednjiLet() const
    {
        auto izlaz=*std::max_element(letovi.begin(),letovi.end(),[](const std::shared_ptr<Let> &let1, const std::shared_ptr<Let> &let2) {
            return (let1->DajOcekivanoVrijemePolijetanja().first*60+let1->DajOcekivanoVrijemePolijetanja().second)
                   >(let2->DajOcekivanoVrijemePolijetanja().first*60+let2->DajOcekivanoVrijemePolijetanja().second);
        });
        return *izlaz;
    }
    void RegistrirajLet(const char odrediste[], const char oznaka_leta[],int kapija, int sat_polaska, int minute_polaska, int trajanje_leta);
    void RegistrirajLet(std::shared_ptr<Let> let);
    int DajBrojLetova() const
    {
        letovi.size();
    }
    int DajBrojLetovaKojiKasne() const
    {
        return std::count_if(letovi.begin(),letovi.end(),[](std::shared_ptr<Let> let) {
            return let->DaLiKasni();
        });
    }
    int DajProsjecnoTrajanjeLetova() const;
    void IsprazniKolekciju()
    {
        for(int i=0; i<letovi.size(); i++)
            letovi.at(i)=nullptr;
        letovi.resize(0);
    }
    void Ispisi(int sati, int minute) const;
};
Letovi::Letovi(std::initializer_list<Let> lista_letova)
{
    letovi.resize(lista_letova.size());
    auto it=lista_letova.begin();
    for(int i=0; i<lista_letova.size(); i++) {
        letovi[i]=std::make_shared<Let>(*it);
        it++;
    }
}
Letovi::Letovi (const Letovi &l)
{
    letovi.resize(l.letovi.size());
    for(int i=0; i<l.letovi.size(); i++)
        letovi[i]=std::make_shared<Let>(*l.letovi[i]);
}
Letovi::Letovi(Letovi &&l)
{
    std::swap(letovi,l.letovi);
}
void Letovi::RegistrirajLet(const char odrediste[], const char oznaka_leta[],int kapija, int sat_polaska, int minute_polaska, int trajanje_leta)
{
    letovi.push_back(std::make_shared<Let>(Let(odrediste,oznaka_leta,kapija,sat_polaska,minute_polaska,trajanje_leta)));
}
void Letovi::RegistrirajLet(std::shared_ptr<Let> let)
{
    letovi.push_back(let);
}
int Letovi::DajProsjecnoTrajanjeLetova() const
{
    int prosjek=0;
    for(int i=0; i<DajBrojLetova(); i++) {
        prosjek+=letovi[i]->DajTrajanjeLeta();
    }
    return prosjek/DajBrojLetova();
}
void Letovi::Ispisi(int sati, int minute) const
{
    auto letovi_tmp=letovi;
    std::sort(letovi_tmp.begin(),letovi_tmp.end(),[](std::shared_ptr<Let> let1, std::shared_ptr<Let> let2) {
        return (let1->DajOcekivanoVrijemePolijetanja().first*60+let1->DajOcekivanoVrijemePolijetanja().second)
               <(let2->DajOcekivanoVrijemePolijetanja().first*60+let2->DajOcekivanoVrijemePolijetanja().second);
    });
    for(int i=0; i<letovi_tmp.size(); i++)
        if(letovi_tmp[i]->DajOcekivanoVrijemePolijetanja().first>=sati && letovi_tmp[i]->DajOcekivanoVrijemePolijetanja().second>=minute)
            letovi_tmp[i]->Ispisi();
}
int main ()
{
    return 0;
}