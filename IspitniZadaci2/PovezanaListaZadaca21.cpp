// TP 2018/2019: Zadaća 3, Zadatak 5
#include <iostream>
#include <new>
#include <vector>
struct Blok {
    int redni_broj;
    Blok *sljedeci;
};

std::vector<int> Razbrajanje(int N, int M)
{
    std::vector<int> izlazni;
    // kreiranje povezane liste
    Blok *pocetak = nullptr;
    Blok *prethodni;
    for (int i = 1; i <= N; i++) {
        Blok *novi = new Blok{i, nullptr};
        if (!pocetak)
            pocetak = novi;
        else
            prethodni->sljedeci = novi;
        prethodni = novi;
    }
    prethodni->sljedeci = pocetak;
    auto it = pocetak;
    for(int i=0; i<N; i++) {
        pocetak=it;
        izlazni.push_back(it->redni_broj);
        it=it->sljedeci;
        prethodni->sljedeci=it;
        delete pocetak;
        if(i<N-1)
            for(int j=0; j<M-1; j++) {
                prethodni=it;
                it=it->sljedeci;
            }
    }
    return izlazni;
}

int OdabirKoraka(int N, int K)
{
    if (N <= 0 || K <= 0 || K > N)
        throw std::domain_error(
            "Broj blokova i redni broj bloka su pozitivni cijeli brojevi i redni "
            "broj bloka ne moze biti veci od broja blokova");
    int M = 0;
    for (int i = 1; i <= N; i++) {
        std::vector<int> blok_sa_koracima = Razbrajanje(N, i);
        if (blok_sa_koracima.at(blok_sa_koracima.size() - 1) == K) {
            M = i;
            return M;
        }
    }
    return M;
}
int main()
{
    try {
        std::cout << "Unesite broj blokova u gradu: ";
        int N;
        std::cin >> N;
        std::cout
                << "Unesite redni broj bloka u kojem se nalazi sjediste stranke: ";
        int K;
        std::cin >> K;
        std::cout << "Trazeni korak: " << OdabirKoraka(N, K);
    } catch (std::domain_error d) {
        std::cout << d.what();
    }
    return 0;
}
