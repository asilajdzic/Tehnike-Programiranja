//TP 2018/2019: Tutorijal 8, Zadatak 6
#include <iostream>
template <typename Tip>
struct Cvor {
    Tip element;
    Cvor* veza;
};
template <typename TipElementa>
Cvor<TipElementa> *KreirajPovezanuListu(TipElementa zavrsni)
{
    Cvor<TipElementa> *pocetak=nullptr,*prethodni;
    for(;;) {
        TipElementa unos;
        std::cin>>unos;
        if(unos==zavrsni) break;
        Cvor<TipElementa> *novi=new Cvor<TipElementa> {unos,nullptr};
        if(!pocetak) pocetak=novi;
        else prethodni->veza=novi;
        prethodni=novi;
    }
    return pocetak;
}
template <typename TipElementa>
int BrojElemenata (Cvor<TipElementa>*pocetak)
{
    int brojac=0;
    for(auto pok=pocetak; pok!=nullptr; pok=pok->veza)
        brojac++;
    return brojac;
}
template <typename TipElementa>
TipElementa SumaElemenata (Cvor<TipElementa> *pocetak)
{
    TipElementa suma=0;
    for(auto pok=pocetak; pok!=nullptr; pok=pok->veza)
        suma+=pok->element;
    return suma;
}
template <typename TipElementa>
int BrojVecihOd (Cvor<TipElementa>*pocetak, TipElementa prag)
{
    int brojac=0;
    for(auto pok=pocetak; pok!=nullptr; pok=pok->veza)
        if(pok->element>prag)
            brojac++;
    return brojac;
}
template <typename TipElementa>
void UnistiListu(Cvor<TipElementa>*pocetak)
{
    Cvor<TipElementa> *poslije;
    while(pocetak)
    {
        poslije=pocetak->veza;
        delete pocetak;
        pocetak=poslije;
    }
}
int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    Cvor<double> *pocetak=KreirajPovezanuListu<double>(0);
    int veci=BrojVecihOd<double>(pocetak,SumaElemenata<double>(pocetak)/BrojElemenata<double>(pocetak));
    std::cout<<"U slijedu ima "<<veci<<" brojeva vecih od njihove aritmeticke sredine";
    UnistiListu(pocetak);
    return 0;
}
