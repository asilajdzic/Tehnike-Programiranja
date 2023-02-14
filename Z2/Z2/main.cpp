//TP 2018/2019: Zadaća 2, Zadatak 2
#include <iostream>
#include <vector>
#include <type_traits>
#include <algorithm>
template <typename tip>
int SumaProstihFaktora(tip x)
{
    if(x==0 || x==1)
        return x;
    tip suma=0;
    x=abs(x);
    tip i=2;
    while(x!=1) {
        if(x%i==0) {
            while(x%i==0)
                x/=i;
            suma+=i;
        }
        i++;
    }
    return suma;
} // dobra
template<typename tip>
bool JeLiSlobodan(tip n)
{
    n=abs(n);
    for(tip i=2; i*i<=n; i++)
        if(n%(i*i)==0) return false;
    return true;
}
template<typename tip>
auto Izdvajanje(tip p1, tip &p2,int &brojac) -> typename std::remove_reference<decltype(*p1)>::type*
{
    try {
        brojac=0;
        auto adresa=p1;
        while(p1!=p2) {
            if(JeLiSlobodan(*p1)) {
                bool duplikat=false;
                auto tmpKopija=adresa;
                while(tmpKopija!=p1) {
                    if(*tmpKopija==*p1)
                        duplikat=true;
                    tmpKopija++;
                }
                if(!duplikat)
                    brojac++;
            }
            p1++;
        } // brojac
        p1=adresa;
        auto nizIzdvojenih=new typename std::remove_reference<decltype(*p1)>::type[brojac];
        auto krajIzdvojenih=nizIzdvojenih;
        auto adresaIzdvojenih=nizIzdvojenih;
        while(p1!=p2) {
            if(JeLiSlobodan(*p1)) {
                bool duplikat=false;
                while(nizIzdvojenih!=krajIzdvojenih) {
                    if(*p1==*nizIzdvojenih)
                        duplikat=true;
                    nizIzdvojenih++;
                }
                if(!duplikat) {
                    *krajIzdvojenih=*p1;
                    krajIzdvojenih++;
                }
                nizIzdvojenih=adresaIzdvojenih;
            }
            p1++;
        } //dinamicki niz, dobar
        p1=adresa;
        while(p1!=p2) {
            bool trebaIzbrisati=false;
            auto setac=p1+1;
            while(setac!=p2) {
                if(SumaProstihFaktora(*setac)==SumaProstihFaktora(*p1)) {
                    trebaIzbrisati=true;
                    auto setac2=setac;
                    auto setac3=setac+1;
                    while(setac3!=p2)
                        *setac2++=*setac3++;
                    setac--;
                    p2--;
                }
                setac++;
            }
            if(trebaIzbrisati) {
                auto setac2=p1;
                auto setac3=p1+1;
                while(setac3!=p2)
                    *setac2++=*setac3++;
                p1--;
                p2--;
            }
            p1++;
        }
        return nizIzdvojenih;
    } catch(std::bad_alloc) {
        throw std::range_error("Nedovoljno memorije!");
    }
}
int main ()
{
    std::cout<<"Unesite brojeve: ";
    std::vector<int> v;
    for(;;) {
        int x;
        std::cin>>x;
        if(x==-1) break;
        v.push_back(x);
    }
    int brojac;
    auto kraj=v.end();
    auto poc=v.begin();
    auto izdvojeni=Izdvajanje(poc,kraj,brojac);
    std::cout<<"Izdvojeni brojevi: ";
    for(int i=0; i<brojac; i++) {
        std::cout<<izdvojeni[i];
        if(i<brojac-1) std::cout<<", ";
    }
    std::cout<<"\nModificirani kontejner (prije sortiranja): ";
    while(poc!=kraj) {
        if(poc!=kraj-1)
            std::cout<<*poc<<", ";
        else std::cout<<*poc;
        poc++;
    }
    poc=v.begin();
    std::sort(poc,kraj,[](long long int x, long long y) {
        long long int a=x;
        long long int b=y;
        int proizvod=1;
        x=abs(x);
        while(x!=0) {
            int cifra=x%10;
            proizvod*=cifra;
            x/=10;
        }
        int proizvod2=1;
        y=abs(y);
        while(y!=0) {
            int cifra=y%10;
            proizvod2*=cifra;
            y/=10;
        }
        if(proizvod<proizvod2) return true;
        else if(proizvod==proizvod2) return a>b;
        return false;
    });
    std::cout<<"\nModificirani kontejner (nakon sortiranja): ";
    while(poc!=kraj) {
        if(poc!=kraj-1)
            std::cout<<*poc<<", ";
        else std::cout<<*poc;
        poc++;
    }
    delete[] izdvojeni;
    return 0;
}
