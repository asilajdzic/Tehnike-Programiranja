#include <iostream>
#include <vector>
template<class TipElemenata>
class SimetricnaMatrica
{
    std::vector<std::vector<TipElemenata>> simetricnaMatrica;
public:
    SimetricnaMatrica()=default;
    template<class Tip>
    SimetricnaMatrica(const SimetricnaMatrica &m);
    SimetricnaMatrica(const std::vector<std::vector<TipElemenata> &m);
    SimetricnaMatrica(const std::initializer_list<std::initializer_list>> &lista);
    explicit SimetricnaMatrica(int n);
    int DajDimenziju()  const {
        return simetricnaMatrica.size();
    }
    bool operator !()   const {
        for(int i=0;i<simetricnaMatrica.size();i++)
            for(int j=0;j<simetricnaMatrica.at(i).size();j++)
                if(simetricnaMatrica.at(i).at(j)!=0)
                    return false;
        return true;
    }
    
};
int main()
{
    return 0;
}
