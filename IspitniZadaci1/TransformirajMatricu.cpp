#include <iostream>
#include <vector>
#include <list>
std::list<bool> TransformirajMatricu (std::vector<std::vector<double>> &m)
{
    for(int i=0; i<m.size()-1; i++)
        if(m.at(i).size()!=m.at(i+1).size())  throw std::domain_error("Parametar nema formu matrice");
    std::list<bool> l;
    for(int i=0; i<m.size()/2; i++) {
        std::swap(m.at(i),m.at(m.size()-i-1));
    }
    for(int i=0; i<m.at(0).size(); i++) {
        double suma=0;
        for(int j=0; j<m.size(); j++)
            suma+=m.at(j).at(i);
        if(suma==int(suma))  l.push_back(true);
        else l.push_back(false);
    }
    return l;
}
int main()
{
    std::vector<std::vector<double>> m;
    m.push_back({1,2});
    m.push_back({3,4});
    m.push_back({5,6});
    for(int i=0; i<3; i++) {
        for(int j=0; j<2; j++)
            std::cout<<m.at(i).at(j)<<" ";
        std::cout<<"\n";
    }
    auto l=TransformirajMatricu(m);
    for(int i=0; i<3; i++) {
        for(int j=0; j<2; j++)
            std::cout<<m.at(i).at(j)<<" ";
        std::cout<<"\n";
    }
    for(auto x : l)
        std::cout<<x<<" ";
    return 0;
    //treba main napravit, al to je bukvalno unos
}
