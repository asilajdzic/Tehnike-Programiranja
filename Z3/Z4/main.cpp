//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>
#include <list>
int Poglavica(int n, int m, bool trebaIspisati=false)
{
    std::list<int> lista;
    for(int i=1; i<=n; i++)
        lista.push_back(i);
    for(auto it=lista.begin(); lista.size()>1;) {
        for(int i=0; i<m-1; i++) {
            it++;
            if(it==lista.end()) it++;
        }
        if(trebaIspisati)
            std::cout<<*it<<std::endl;
        it=lista.erase(it);
        if(it==lista.end()) it++;
    }
    auto it=lista.begin();
    return *it;
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
    if(sigurnoMjesto<=n1)
        return sigurnoMjesto;
    return 0;
}
int main ()
{
    int m,n,n1,n2;
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
