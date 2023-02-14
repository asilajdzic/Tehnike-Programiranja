#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
std::vector<bool> JesuLiElementiVektoraKuboviPrirodnogBroja(std::vector<int> v)
{
    std::vector<bool> u;
    for(int i=0; i<v.size(); i++) {
        if(v.at(i)<0)   throw std::domain_error("Nepravilni elementi vektora!");
        if(pow(int(cbrt(v.at(i))),3)==v.at(i))
            u.push_back(true);
        else u.push_back(false);
    }
    return u;
}
int main()
{
    std::vector<int> v(10);
    for(int i=0; i<10; i++)
        std::cin>>v.at(i);
    try {
        auto u=JesuLiElementiVektoraKuboviPrirodnogBroja(v);
        for(int i=0; i<u.size(); i++)
            std::cout<<u.at(i)<<" ";
    } catch(std::domain_error dp) {
        std::cout<<dp.what();
    }
    return 0;
}
