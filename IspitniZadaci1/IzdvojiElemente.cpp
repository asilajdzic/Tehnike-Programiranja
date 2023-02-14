#include <iostream>
#include <deque>
#include <vector>
#include <cmath>
#include <stdexcept>
template<typename Tip>
std::deque<double> IzdvojiElemente (std::vector<Tip> v)
{
    std::deque<double> d;
    for(int i=0; i<v.size(); i++) {
        if(v.at(i)%2)
            d.push_back(v.at(i)*v.at(i));
        else if(v.at(i)%2==0 && v.at(i)>0)
            d.push_back(sqrt(v.at(i)));
        else if(v.at(i)<0)  throw std::logic_error("Element vektora negativan");
    }
    return d;
}
int main()
{
    std::cout<<"Unesite broj elemenata vektora: ";
    int n;
    std::cin>>n;
    std::vector<int> v(n);
    for(int i=0; i<v.size(); i++)
        std::cin>>v.at(i);
    try {
        auto d=IzdvojiElemente<int>(v);
        std::cout<<"Rezutujući dek: ";
        for(int i=0; i<d.size(); i++)    std::cout<<d.at(i)<<" ";
    } catch(std::logic_error e) {
        std::cout<<e.what();
    }
    return 0;
}
