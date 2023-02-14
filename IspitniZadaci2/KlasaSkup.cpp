#include <iostream>
#include <vector>
template<typename Tip>
class Skup
{
    std::vector<Tip> skup;
public:
    Skup () =default;
    template<typename Tip2>
    Skup(std::initializer_list<Tip2> lista)
    {
        for(auto it=lista.begin(); it!=lista.end(); it++)
            Dodaj(*it);
    }
    int Velicina()  const
    {
        return skup.size();
    }
    void Dodaj(Tip element)
    {
        if(!ImaLiGa(element)) {
            auto it=skup.begin();
            for(; it!=skup.end(); it++) {
                if(*it>element)  break;
            }
            skup.insert(it,element);
        }
    }
    void Izbrisi(Tip element)
    {
        if(ImaLiGa(element)) {
            auto it=skup.begin();
            for(; it!=skup.end(); it++)
                if(*it==element)    break;
            skup.erase(it);
        }
    }
    bool ImaLiGa(Tip element)   const
    {
        for(int i=0; i<skup.size(); i++)
            if(skup.at(i)==element) return true;
        return false;
    }
    void Ispisi()   const
    {
        for(int i=0; i<skup.size(); i++)
            std::cout<<skup.at(i)<<" ";
    }
};
int main()
{
    Skup<int> A{1,2,6,4,2,5,8,4,2,1};
    A.Ispisi();
    std::cout<<"\n";
    A.Dodaj(0);
    A.Ispisi();
    std::cout<<"\n";
    A.Izbrisi(2);
    A.Dodaj(-10000);
    A.Ispisi();
    std::cout<<"\n";
    return 0;
}
