// TP 2018/2019: Zadaća 3, Zadatak 6
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

struct Blok {
    int rednibroj;
    std::shared_ptr<Blok> sljedeci;
};

std::shared_ptr<Blok> KreirajPovezanuListu(int brblokova)
{
    std::shared_ptr<Blok> pocetak = nullptr, prethodni;
    for (int i = 1; i <= brblokova; i++) {
        std::shared_ptr<Blok> novi = std::make_shared<Blok>();
        novi->rednibroj = i;
        novi->sljedeci = nullptr;
        if (pocetak == nullptr)
            pocetak = novi;
        else
            prethodni->sljedeci = novi;
        prethodni = novi;
    }
    prethodni->sljedeci = pocetak;
    return pocetak;
}

std::vector<int> Razbrajanje(int brblokova, int M)
{
    auto p = KreirajPovezanuListu(brblokova);
    auto tmp=p;
    std::vector<int> redoslijed;
    while(redoslijed.size()<brblokova) {
        redoslijed.push_back(tmp->rednibroj);
        tmp->rednibroj=0;
        for(int i=0; i<M; i++) {
            tmp=tmp->sljedeci;
            while(redoslijed.size()<brblokova && tmp->rednibroj==0) tmp=tmp->sljedeci;
        }
    }
    //ovdje samo brisem tj postavljam na nullptr ovu listu, najbolje bi bilo brisati odmah
    // umjesto ovog mog postavljanja rednog broja na 0, ali nisam u formi pa sam se nakon dosta patnje predao
    tmp=p;
    while(tmp->sljedeci!=p) {
        auto prethodni=tmp;
        tmp=tmp->sljedeci;
        prethodni=nullptr;
    }
    p->sljedeci=nullptr;
    p=nullptr;
    return redoslijed;
}

int OdabirKoraka(int brblokova, int K)
{
    if (brblokova <= 0 || K <= 0 || K > brblokova)
        throw std::domain_error(
            "Broj blokova i redni broj bloka su pozitivni cijeli brojevi i redni "
            "broj bloka ne moze biti veci od broja blokova");
    for (int i = 1; i < brblokova; i++) {
        std::vector<int> redoslijed = Razbrajanje(brblokova, i);
        int posljednji = redoslijed.at(redoslijed.size() - 1);
        if (posljednji == K)
            return i;
    }
    return 0;
}

int main()
{
    try {
        std::cout << "Unesite broj blokova u gradu: ";
        int brblokova;
        std::cin >> brblokova;
        std::cout
                << "Unesite redni broj bloka u kojem se nalazi sjediste stranke: ";
        int m;
        std::cin >> m;
        std::cout << "Trazeni korak: " << OdabirKoraka(brblokova, m);
    } catch (std::domain_error izuzetak) {
        std::cout << izuzetak.what();
    }
    return 0;
}
