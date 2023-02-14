#include <iostream>
#include <set>
#include <vector>
#include <string>
int funkcija(int a, int b)
{
    return a*a+b*b;
}
template<class ulaz, class funkcija>
auto Umotaj(ulaz v, funkcija f)->typename std::remove_reference<decltype(v)>::type
{
    ulaz izlaz;
    auto it2=izlaz.begin();
    auto a0=*(v.begin())-*(v.begin());
    //nisam siguran da mogu svi kontejneri ovako,
    //tipa string ili nešto, ako imaš ideju bujrum :D
    for(auto it=v.begin(); it!=v.end(); it++) {
        izlaz.insert(izlaz.end(),f(a0,*it));
        a0=f(a0,*it);
    }
    return izlaz;
}
int main()
{
    std::set<int> s;
    std::cout<<"Unesi 4 elemenata skupa: ";
    for(int i=0; i<4; i++) {
        int a;
        std::cin>>a;
        s.insert(a);
    }
    std::vector<int> v(4);
    std::cout<<"Unesi 4 elemenata vektora: ";
    for(int i=0; i<4; i++)
        std::cin>>v.at(i);
    auto set=Umotaj(s,funkcija);
    auto vektor=Umotaj(v,funkcija);
    std::cout<<"\nSet:\n";
    for(auto x : set)
        std::cout<<x<<" ";
    std::cout<<"\nVektor:\n";
    for(auto x : vektor)
        std::cout<<x<<" ";
    return 0;
}
