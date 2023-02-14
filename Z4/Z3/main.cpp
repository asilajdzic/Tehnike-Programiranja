//TP 2018/2019: Zadaća 4, Zadatak 3
#include <iostream>
#include <string.h>
#include <iomanip>
#include <algorithm>
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
    int broj_letova;
    const int max_br_letova;
    Let **letovi;
public:
    explicit Letovi(int max_broj_letova);
    Letovi(std::initializer_list<Let> lista_letova);
    ~Letovi();
    Letovi(const Letovi &letovi);
    Letovi(Letovi &&letovi);
    Letovi &operator =(const Letovi &l)
    {
        if(max_br_letova<l.broj_letova) throw std::logic_error("Nesaglasni kapaciteti liga");
        for(int i=0; i<broj_letova; i++)	delete letovi[i];
        delete [] letovi;
        letovi=new Let*[l.broj_letova];
        if(broj_letova>=l.broj_letova)
            for(int i=0; i<l.broj_letova; i++)
                letovi[i]=new Let(*l.letovi[i]);
        else
            for(int i=0; i<l.broj_letova; i++)
                letovi[i]=new Let(*l.letovi[i]);
        broj_letova=l.broj_letova;
        return *this;
    }
    Letovi &operator =(Letovi &&l)
    {
        if(max_br_letova<l.broj_letova) throw std::logic_error("Nesaglasni kapaciteti liga");
        for(int i=0; i<broj_letova; i++)	delete letovi[i];
        delete [] letovi;
        letovi=new Let*[l.broj_letova];
        if(broj_letova>=l.broj_letova)
            for(int i=0; i<l.broj_letova; i++)
                letovi[i]=new Let(*l.letovi[i]);
        else
            for(int i=0; i<l.broj_letova; i++)
                letovi[i]=new Let(*l.letovi[i]);
        broj_letova=l.broj_letova;
        l.letovi=nullptr;
        return *this;
    }
    void RegistrirajLet(const char odrediste[], const char oznaka_leta[],int kapija, int sat_polaska, int minute_polaska, int trajanje_leta);
    void RegistrirajLet(Let *let);
    int DajBrojLetova() const
    {
        return broj_letova;
    }
    int DajBrojLetovaKojiKasne() const
    {
        return std::count_if(letovi,letovi+broj_letova,[](Let *let) {
            return let->DaLiKasni();
        });
    }
    int DajProsjecnoTrajanjeLetova() const;
    Let &DajPrviLet() const
    {
        auto let=*std::min_element(letovi,letovi+DajBrojLetova(),[](Let *let1,Let *let2) {
            auto polazak1=let1->DajOcekivanoVrijemePolijetanja();
            auto polazak2=let2->DajOcekivanoVrijemeSlijetanja();
            return polazak1.first*60+polazak1.second<polazak2.first*60+polazak2.second;
        });
        return let[0];
    }
    Let &DajPosljednjiLet() const
    {
        auto let=*std::max_element(letovi,letovi+DajBrojLetova(),[](Let *let1,Let *let2) {
            auto polazak1=let1->DajOcekivanoVrijemePolijetanja();
            auto polazak2=let2->DajOcekivanoVrijemeSlijetanja();
            return polazak1.first*60+polazak1.second<polazak2.first*60+polazak2.second;
        });
        return let[0];
    }
    void IsprazniKolekciju()
    {
        for(int i=0; i< broj_letova; i++) delete letovi[i];
        broj_letova=0;
    }
    void Ispisi(int sati, int minute) const;
};
Letovi::Letovi(int max_broj_letova): max_br_letova(max_broj_letova)
{
    letovi=new Let*[max_broj_letova];
    broj_letova=0;
}
Letovi::Letovi(std::initializer_list<Let> lista_letova) :max_br_letova(lista_letova.size())
{
    letovi=new Let*[lista_letova.size()];
    auto it=lista_letova.begin();
    for(int i=0; i<lista_letova.size(); i++) {
        letovi[i]=new Let(*it);
        it++;
    }
    broj_letova=lista_letova.size();
}
Letovi::~Letovi()
{
    for(int i=0; i<broj_letova; i++)	delete letovi[i];
    delete[] letovi;
}
Letovi::Letovi (const Letovi &l): max_br_letova(l.max_br_letova)
{
    letovi=new Let*[l.broj_letova];
    for(int i=0; i<l.broj_letova; i++)
        letovi[i]=new Let(*(l.letovi[i]));
    broj_letova=l.broj_letova;
}
Letovi::Letovi(Letovi &&l): max_br_letova(l.max_br_letova)
{
    letovi=new Let*[l.broj_letova];
    for(int i=0; i<l.broj_letova; i++)
        letovi[i]=new Let(*(l.letovi[i]));
    broj_letova=l.broj_letova;
    l.letovi=nullptr;
}
void Letovi::RegistrirajLet(const char odrediste[], const char oznaka_leta[],int kapija, int sat_polaska, int minute_polaska, int trajanje_leta)
{
    if(broj_letova>max_br_letova-1) throw std::range_error("Dostignut maksimalni broj letova");
    try {
        letovi[broj_letova]=new Let(odrediste,oznaka_leta,kapija,sat_polaska,minute_polaska,trajanje_leta);
        broj_letova++;
    } catch(...) {
        throw;
    }
}
void Letovi::RegistrirajLet(Let *let)
{
    if(broj_letova>max_br_letova-1) throw std::range_error("Dostignut maksimalni broj letova");
    letovi[broj_letova]=let;
    let=nullptr;
    broj_letova++;
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
    std::sort(letovi,letovi+broj_letova,[](Let *let1, Let *let2) {
        auto polazak1=let1->DajOcekivanoVrijemePolijetanja();
        auto polazak2=let2->DajOcekivanoVrijemePolijetanja();
        return polazak1.first*60+polazak1.second<polazak2.first*60+polazak2.second;
    });
    for(int i=0; i<broj_letova; i++)
        if(letovi[i]->DajOcekivanoVrijemePolijetanja().first>=sati && letovi[i]->DajOcekivanoVrijemePolijetanja().second>=minute)
            letovi[i]->Ispisi();
} // belaj je sto je const metoda, a sort mijenja redoslijed...
int main ()
{
    Letovi letovi2(5);
    Letovi letovi(3);
    letovi.RegistrirajLet("A", "B", 1, 0, 0, 100);
    letovi.RegistrirajLet("A1", "B2", 1, 0, 0, 100);
    letovi.RegistrirajLet("A2", "B2", 1, 0, 0, 100);
    letovi.IsprazniKolekciju();
    letovi=letovi2;
    letovi.RegistrirajLet("Odrediste2", "Oznaka2", 20, 12, 12, 250);
    Let* let = new Let("Odrediste", "Oznaka", 10, 10, 10, 300);
    let->PostaviKasnjenje(100);
    letovi.RegistrirajLet(let);
    letovi.RegistrirajLet("A", "B", 1, 0, 55, 100);
    letovi.Ispisi(5,5);
    return 0;
}
