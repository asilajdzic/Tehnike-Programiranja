//TP 2018/2019: Zadaća 4, Zadatak 5
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <memory>
struct Korisnik {
    std::string ime,prezime,adresa,telefon;
};
class Knjiga
{
    std::string naziv_knjige, ime_pisca, zanr;
    int godina_izdavanja;
    Korisnik* zaduzio=nullptr;
public:
    Knjiga(std::string naziv_knjige, std::string ime_pisca, std::string zanr, int godina_izdavanja);
    std::string DajNaslov() const
    {
        return naziv_knjige;
    }
    std::string DajAutora() const
    {
        return ime_pisca;
    }
    std::string DajZanr()   const
    {
        return zanr;
    }
    int DajGodinuIzdavanja()    const
    {
        return godina_izdavanja;
    }
    Korisnik* DajKodKogaJe()    const
    {
        return zaduzio;
    }
    void ZaduziKnjigu(Korisnik &korisnik);
    void RazduziKnjigu()
    {
        zaduzio=nullptr;
    }
    bool DaLiJeZaduzena()   const
    {
        if(zaduzio) return true;
        return false;
    }
};
Knjiga::Knjiga(std::string naziv_knjige, std::string ime_pisca, std::string zanr, int godina_izdavanja)
{
    Knjiga::naziv_knjige=naziv_knjige;
    Knjiga::ime_pisca=ime_pisca;
    Knjiga::zanr=zanr;
    Knjiga::godina_izdavanja=godina_izdavanja;
    Knjiga *zaduzio=nullptr;
}
void Knjiga::ZaduziKnjigu(Korisnik &korisnik)
{
    if(DaLiJeZaduzena()) throw std::logic_error("Knjiga vec zaduzena");
    zaduzio=&korisnik;
}
class Biblioteka
{
    std::map<int, std::shared_ptr<Korisnik>> mapa_korisnika;
    std::map<int, std::shared_ptr<Knjiga>> mapa_knjiga;
public:
    Biblioteka() {}
    Biblioteka(const Biblioteka &biblioteka);
    Biblioteka(Biblioteka &&biblioteka);
    Biblioteka &operator =(const Biblioteka &biblioteka)
    {
        for(auto it=biblioteka.mapa_knjiga.begin(); it!=biblioteka.mapa_knjiga.end(); it++)
            mapa_knjiga[it->first]=std::make_shared<Knjiga>(*it->second);
        for(auto it=biblioteka.mapa_korisnika.begin(); it!=biblioteka.mapa_korisnika.end(); it++)
            mapa_korisnika[it->first]=std::make_shared<Korisnik>(*it->second);
        return *this;
    }
    Biblioteka &operator =(Biblioteka &&biblioteka)
    {
        std::swap(mapa_knjiga,biblioteka.mapa_knjiga);
        std::swap(mapa_korisnika,biblioteka.mapa_korisnika);
        return *this;
    }
    ~Biblioteka();
    void RegistrirajNovogKorisnika(int id, std::string ime, std::string prezime, std::string adresa, std::string telefon);
    void RegistrirajNovuKnjigu(int id, std::string naziv_knjige, std::string ime_pisca, std::string zanr, int godina_izdavanja);
    Korisnik &NadjiKorisnika(int id_korisnika)    const;
    Knjiga &NadjiKnjigu(int id_knjige) const;
    void IzlistajKorisnike()    const;
    void IzlistajKnjige()   const;
    void ZaduziKnjigu(int id_knjige, int id_korisnika);
    void RazduziKnjigu(int id_knjige)
    {
        mapa_knjiga[id_knjige]->RazduziKnjigu();
    }
    void PrikaziZaduzenja(int id_korisnika) const;

};
Biblioteka::Biblioteka(const Biblioteka &biblioteka)
{
    for(auto it=biblioteka.mapa_knjiga.begin(); it!=biblioteka.mapa_knjiga.end(); it++)
        mapa_knjiga[it->first]=std::make_shared<Knjiga>(*it->second);
    for(auto it=biblioteka.mapa_korisnika.begin(); it!=biblioteka.mapa_korisnika.end(); it++)
        mapa_korisnika[it->first]=std::make_shared<Korisnik> (*it->second);
}
Biblioteka::Biblioteka(Biblioteka &&biblioteka)
{
    std::swap(mapa_knjiga,biblioteka.mapa_knjiga);
    std::swap(mapa_korisnika,biblioteka.mapa_korisnika);
}
Biblioteka::~Biblioteka()
{
    for(auto it=mapa_knjiga.begin(); it!=mapa_knjiga.end(); it++)
        it->second=nullptr;
    for(auto it=mapa_korisnika.begin(); it!=mapa_korisnika.end(); it++)
       it->second=nullptr;
}
void Biblioteka::RegistrirajNovogKorisnika(int id, std::string ime, std::string prezime, std::string adresa, std::string telefon)
{
    if(mapa_korisnika.count(id))
        throw std::logic_error ("Korisnik vec postoji");
    Korisnik kor={ime,prezime,adresa,telefon};
    mapa_korisnika[id]=std::make_shared<Korisnik>(kor);
}
void Biblioteka::RegistrirajNovuKnjigu(int id, std::string naziv_knjige, std::string ime_pisca, std::string zanr, int godina_izdavanja)
{
    if(mapa_knjiga.count(id))  throw std::logic_error ("Knjiga vec postoji");
    mapa_knjiga[id]=std::make_shared<Knjiga>(Knjiga(naziv_knjige,ime_pisca,zanr,godina_izdavanja));
}
Korisnik &Biblioteka::NadjiKorisnika(int id_korisnika)    const
{
    if(!mapa_korisnika.count(id_korisnika))
        throw std::logic_error("Korisnik nije nadjen");
    return *(mapa_korisnika.find(id_korisnika)->second);

}
Knjiga &Biblioteka::NadjiKnjigu(int id_knjige)    const
{
    if(!mapa_knjiga.count(id_knjige))
        throw std::logic_error("Knjiga nije nadjena");
    return *(mapa_knjiga.find(id_knjige)->second);

}
void Biblioteka::IzlistajKorisnike()    const
{
    for(auto it=mapa_korisnika.begin(); it!=mapa_korisnika.end(); it++) {
        std::cout<<"Clanski broj: "<<it->first<<std::endl
                 <<"Ime i prezime: "<<it->second->ime<<" "<<it->second->prezime<<std::endl<<
                 "Adresa: "<<it->second->adresa<<std::endl<<
                 "Broj telefona: "<<it->second->telefon<<std::endl;
    }
}
void Biblioteka::IzlistajKnjige()    const
{
    for(auto it=mapa_knjiga.begin(); it!=mapa_knjiga.end(); it++) {
        std::cout<<"Evidencijski broj: "<<it->first<<std::endl
                 <<"Naslov: "<<it->second->DajNaslov()<<std::endl<<
                 "Pisac: "<<it->second->DajAutora()<<std::endl<<
                 "Zanr: "<<it->second->DajZanr()<<std::endl<<
                 "Godina izdavanja: "<<it->second->DajGodinuIzdavanja()<<std::endl;
        if(it->second->DaLiJeZaduzena())
            std::cout<<"Zaduzena kod korisnika: "<<it->second->DajKodKogaJe()->ime<<" "<<it->second->DajKodKogaJe()->prezime<<std::endl;
        std::cout<<std::endl;
    }
}
void Biblioteka::ZaduziKnjigu(int id_knjige, int id_korisnika)
{
    if(!mapa_knjiga.count(id_knjige))   throw std::logic_error ("Knjiga nije nadjena");
    if(mapa_knjiga.find(id_knjige)->second->DaLiJeZaduzena())    throw std::logic_error ("Knjiga vec zaduzena");
    if(!mapa_korisnika.count(id_korisnika)) throw std::logic_error ("Korisnik nije nadjen");
    auto knjiga=mapa_knjiga.find(id_knjige)->second;
    auto korisnik=mapa_korisnika.find(id_korisnika)->second;
    knjiga->ZaduziKnjigu(*korisnik);
}
void Biblioteka::PrikaziZaduzenja(int id_korisnika) const
{
    try {
        auto korisnik=NadjiKorisnika(id_korisnika);
        for(auto it=mapa_knjiga.begin(); it!=mapa_knjiga.end(); it++) {
            auto korisnik2=*(it->second->DajKodKogaJe());
            if(korisnik.ime==korisnik2.ime && korisnik.prezime==korisnik2.prezime && korisnik.adresa == korisnik2.adresa && korisnik.telefon==korisnik2.telefon) {
                std::cout<<"Evidencijski broj: "<<it->first<<std::endl
                         <<"Naslov: "<<it->second->DajNaslov()<<std::endl<<
                         "Pisac: "<<it->second->DajAutora()<<std::endl<<
                         "Zanr: "<<it->second->DajZanr()<<std::endl<<
                         "Godina izdavanja: "<<it->second->DajGodinuIzdavanja()<<std::endl<<std::endl;
            }
        }
    } catch(...) {
        throw;
    }
}
int main ()
{
    Korisnik kor{"Meho", "Mehic", "Dobojska 15", "033/123-456"};
    Knjiga knj("Tvrdjava", "Mesa Selimovic", "Roman", 1965);
    if(knj.DajKodKogaJe() == nullptr) std::cout << "Nije zaduzena\n";
    std::cout << knj.DaLiJeZaduzena() << std::endl;
    knj.ZaduziKnjigu(kor);
    std::cout << "Knjigu je zaduzio " << knj.DajKodKogaJe()->ime << std::endl;
    std::cout << knj.DaLiJeZaduzena() << std::endl;
    Biblioteka bib8;
    bib8.RegistrirajNovogKorisnika(1, "Niko", "Nikic", "Zmaja od Bosne bb", "123 456");
    bib8.RegistrirajNovuKnjigu(1, "Vlak u snijegu2", "Mato Lovrak2", "Roman2", 1941);
    bib8.RegistrirajNovuKnjigu(2, "Vlak u snijegu", "Mato Lovrak", "Roman", 1931);
    bib8.ZaduziKnjigu(2, 1);
    bib8.IzlistajKnjige();
    return 0;
}
