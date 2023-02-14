//TP 2018/2019: Zadaća 3, Zadatak 2
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <set>
#include <stdexcept>
#include <map>
typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::map<std::string,std::set<std::tuple<std::string, int, int>>> IndeksPojmova;
std::set<std::tuple<std::string,int,int>> PretraziIndeksPojmova(std::string s, IndeksPojmova indeksPojmova)
{
    std::set<std::tuple<std::string,int,int>> set;
    auto mjesto=indeksPojmova.find(s);
    if(mjesto==indeksPojmova.end())  throw   std::logic_error("Pojam nije nadjen");
    return mjesto->second;
} //trebalo bi da je ok
IndeksPojmova KreirajIndeksPojmova(Knjiga knjiga)
{
    IndeksPojmova indeksPojmova;
    for(auto itKnjiga=knjiga.begin(); itKnjiga!=knjiga.end(); itKnjiga++) { //poglavlje po poglavlje
        for(int i=0; i<itKnjiga->second.size(); i++) {  //stranica po stranica
            std::string stranica=itKnjiga->second[i];
            for(int j=0; j<stranica.length(); j++)
                stranica.at(j)=std::tolower(stranica.at(j));
            for(int j=0; j<stranica.length(); j++) { //rijec po rijec
                std::string rijec;
                if((stranica.at(j)>='a' && stranica.at(j)<='z') || (stranica.at(j)>='0' && stranica.at(j)<='9')) {
                    while(j<stranica.length() && ((stranica.at(j)>='a' && stranica.at(j)<='z') || (stranica.at(j)>='0' && stranica.at(j)<='9'))) {
                        rijec.push_back(stranica.at(j));
                        j++;
                    }
                    indeksPojmova[rijec].insert(std::make_tuple(itKnjiga->first,i+1,j-rijec.length()));
                }
            }
        }

    }
    return indeksPojmova;
}
void IspisiIndeksPojmova(IndeksPojmova indeksPojmova)
{
    for(auto it=indeksPojmova.begin(); it!=indeksPojmova.end(); it++) {
        std::cout<<it->first<<": ";
        std::set<std::tuple<std::string, int, int>> set=it->second;
        for(auto it2=set.begin(); it2!=set.end(); it2++) {
            auto it3=it2;
            it3++;
            std::cout<<std::get<0>(*it2)<<"/"<<std::get<1>(*it2)<<"/"<<std::get<2>(*it2);
            if(it3!=set.end())
                std::cout<<", ";
            it3++;
        }
        std::cout<<std::endl;
    }
}
int main ()
{
    std::string imePoglavlja;
    Knjiga knjiga;
    for(;;) {
        std::cout<<"Unesite naziv poglavlja: ";
        std::cin>>imePoglavlja;
        std::string sadrzajStranice;
        std::cin.ignore(10000, '\n');
        if(imePoglavlja==".")
            break;
        for(int i=1;;i++) {
            sadrzajStranice.erase(sadrzajStranice.begin(),sadrzajStranice.end());
            std::cout<<"Unesite sadrzaj stranice "<<i<<": ";
            std::getline(std::cin, sadrzajStranice);
            if(sadrzajStranice==".") break;
            knjiga[imePoglavlja].push_back(sadrzajStranice);
        }
    }
    std::cout<<"\nKreirani indeks pojmova:\n";
    auto indeksPojmova=KreirajIndeksPojmova(knjiga);
    IspisiIndeksPojmova(indeksPojmova);
    std::string rijec;
    for(;;) {
        std::cout<<"Unesite rijec: ";
        std::cin>>rijec;
        if(rijec==".")
            break;
        try {
            auto set=PretraziIndeksPojmova(rijec,indeksPojmova);
            for(auto it=set.begin(); it!=set.end(); it++)
                std::cout<<std::get<0>(*it)<<"/"<<std::get<1>(*it)<<"/"<<std::get<2>(*it)<<" ";
        } catch(std::logic_error) {
            std::cout<<"Unesena rijec nije nadjena!";
        }
        std::cout<<std::endl;
    }
    return 0;
}
