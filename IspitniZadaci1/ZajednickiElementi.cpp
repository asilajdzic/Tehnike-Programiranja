#include <iostream>
#include <vector>
#include <string>
template<typename Tip>
auto ZajednickiElementi(std::vector<Tip> v1, std::vector<Tip> v2)->decltype(v1)
{
    std::vector<Tip> v;
    for(int i=0; i<v1.size(); i++)
        for(int j=0; j<v2.size(); j++)
            if(v1.at(i)==v2.at(j)) {
                bool treba=true;
                for(int k=0; k<v.size(); k++)
                    if(v1.at(i)==v.at(k))   treba=false;
                if(treba) v.push_back(v1.at(i));
            }
    return v;
}
int main()
{
    std::vector<std::string> v1(5);
    std::vector<std::string> v2(5);
    std::cout<<"Elementi prvog vektora:\n";
    for(int i=0; i<5; i++)
        std::cin>>v1.at(i);
    std::cout<<"\nElementi drugog vektora:\n";
    for(int i=0; i<5; i++)
        std::cin>>v2.at(i);
    auto v=ZajednickiElementi(v1,v2);
    for(int i=0; i<v.size(); i++)
        std::cout<<"\n"<<v.at(i);
    return 0;
}
