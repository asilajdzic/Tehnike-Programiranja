#include <iostream>
#include <vector>
bool IdempotentnaMatrica(const std::vector<std::vector<double>> &m)
{
    if(m.size() && m.size()!=m.at(0).size()) return false;
    for(int i=0; i<m.size()-1; i++)
        if(m.at(i).size()!=m.at(i+1).size())    return false;
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m.size(); j++) {
            double suma=0;
            for(int k=0; k<m.size(); k++)
                suma+=m.at(i).at(k)*m.at(k).at(j);
            if(m.at(i).at(j)!=suma) return false;
        }
    }
    return true;
}
int main()
{
    //trebalo bi da radi
    return 0;
}
