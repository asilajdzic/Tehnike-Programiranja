#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
std::deque<double> ObrniPoRedovima(std::vector<std::vector<double>> &v)
{
    std::deque<double> d;
    for(int i=0; i<v.size()-1; i++)
        if(v.at(i).size()!=v.at(i+1).size())    throw std::domain_error("Parametar nema formu matrice");
    for(int i=0; i<v.at(0).size(); i++) {
        double suma=0;
        for(int j=0; j<v.size(); j++)
            suma+=v.at(j).at(i);
        d.push_back(suma);
    }
    for(int i=0; i<v.size()/2; i++)
        std::swap(v.at(i),v.at(v.size()-1-i));
    return d;
}
int main()
{
    std::vector<std::vector<double>> m;
    for(int i=0; i<5; i++) {
        std::vector<double> v(5);
        for(int j=0; j<5; j++)
            std::cin>>v.at(j);
        m.push_back(v);
    }
    try {
        auto d=ObrniPoRedovima(m);
        for(auto x : d)
            std::cout<<x<<" ";
        std::cout<<"\n";
        for(int i=0; i<5; i++) {
            for(int j=0; j<5; j++)
                std::cout<<m.at(i).at(j)<<" ";
            std::cout<<"\n";
        }
    } catch(std::domain_error e) {
        std::cout<<e.what();
    }
    return 0;
}
