#include<iostream>
#include<set>
#include<vector>
int funkcija(int n)
{
    int suma=0;
    while(n!=0) {
        suma+=n%10;
        n/=10;
    }
    return suma;
}
template <class ulaz, class funkcija>
auto Mapiraj(ulaz m, funkcija f) ->typename std::remove_reference<decltype(m)>::type
{
    ulaz izlaz;
    for(auto it=m.begin(); it!=m.end(); it++)
        izlaz.insert(izlaz.end(),f(*it));
    return izlaz;
}
int main()
{
    std::set<int> s;
    std::cout<<"Unesi 3 elemenata skupa: ";
    for(int i=0; i<3; i++) {
        int a;
        std::cin>>a;
        s.insert(a);
    }
    std::vector<int> v(4);
    std::cout<<"Unesi 4 elemenata vektora: ";
    for(int i=0; i<4; i++)
        std::cin>>v.at(i);
    auto set=Mapiraj(s,funkcija);
    auto vektor=Mapiraj(v,funkcija);
    std::cout<<"\nSet:\n";
    for(auto x : set)
        std::cout<<x<<" ";
    std::cout<<"\nVektor:\n";
    for(auto x : vektor)
        std::cout<<x<<" ";
    return 0;
}
