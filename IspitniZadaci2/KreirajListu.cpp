#include <iostream>
#include <list>
#include <complex>
struct Kompleksni {
    double re, im;
    Kompleksni *sljedeci;
};
Kompleksni* KreirajListu(std::list<std::complex<double>> l)
{
    Kompleksni* pocetak=nullptr,*prethodni;
    for(auto it=l.begin(); it!=l.end(); it++) {
        Kompleksni *novi=new Kompleksni{it->real(),it->imag(),nullptr};
        if(!pocetak)    pocetak=novi;
        else prethodni->sljedeci=novi;
        prethodni=novi;
    }
    return pocetak;
}
int main()
{
    std::list<std::complex<double>>l;
    l.push_back({1,2});
    l.push_back({3,4});
    l.push_back({5,6});
    auto lista=KreirajListu(l);
    while(lista) {
        std::cout<<lista->re<<" "<<lista->im<<std::endl;
        auto zaizbrisati=lista;
        lista=lista->sljedeci;
        delete zaizbrisati;
    }
    return 0;
}
