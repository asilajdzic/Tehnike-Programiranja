#include <iostream>
#include <memory>
struct Clan {
    int redni_broj;
    std::shared_ptr<Clan> sljedeci;
};
std::shared_ptr<Clan> KreirajPovezanuListu(int zavrsni)
{
    std::shared_ptr<Clan> pocetak=nullptr,prethodni;
    for(int i=1; i<=zavrsni; i++) {
        auto novi=std::shared_ptr<Clan>(new Clan{i,nullptr});
        if(!pocetak) pocetak=novi;
        else prethodni->sljedeci=novi;
        prethodni=novi;
    }
    prethodni->sljedeci=pocetak;
    return pocetak;
}
int Poglavica(int n, int m, bool trebaIspisati=false)
{
    if(!n) return 0;
    if(m==1) return n;
    auto pocetak=KreirajPovezanuListu(n);
    int brojPreostalih=n;
    auto it=pocetak;
    for(it=pocetak; brojPreostalih>1; brojPreostalih--) {
        for(int i=0; i<m-2; i++) {
            it=it->sljedeci;
        }
        if(trebaIspisati)
            std::cout<<it->redni_broj<<std::endl;
        auto clanPrije=it;
        it=it->sljedeci;
        auto clanPoslije=it->sljedeci;
        clanPrije->sljedeci=clanPoslije;
        it=nullptr;
        it=clanPoslije;
    }
    int izlaz= it->redni_broj;
    it->sljedeci=nullptr;
    it=nullptr;
    return izlaz;
}
int SigurnoMjesto(int m, int n1, int n2)
{
    if(n1<=1) return 0;
    auto niz=new int[n2];
    for(int i=0; i<n2; i++)
        niz[i]=i+1;
    for(int n=n1; n<n2; n++) {
        niz[Poglavica(n,m)-1]=0;
    }
    int sigurnoMjesto=0;
    for(int i=0; i<n2; i++)
        if(niz[i]) {
            sigurnoMjesto=niz[i];
            break;
        }
    delete[] niz;
    if(sigurnoMjesto>n1)
        return 0;
    return sigurnoMjesto;
}
int main ()
{
    int m,n,n1,n2;++
    std::cout<<"Unesi broj punoljetnih clanova (N): ";
    std::cin>>n;
    std::cout<<"Unesi korak razbrajanja (M): ";
    std::cin>>m;
    std::cout<<"Unesi raspon (N1-N2): ";
    std::cin>>n1>>n2;
    std::cout<<"Redni broj osobe koja postaje poglavica: "<<Poglavica(n,m)<<" ";
    if(SigurnoMjesto(m,n1,n2))
        std::cout<<"Sigurno mjesto: "<<SigurnoMjesto(m,n1,n2);
    else std::cout<<"Nema sigurnog mjesta";
    return 0;
}
