#include <iostream>
#include <string>
//nesta nije ok
int OgradiRijec(std::string &s, int n)
{
    int brojac=0;
    std::string tmp;
    bool razmak=true;
    bool zavrseno=false;
    for(int i=0; i<s.length(); i++) {
        tmp.push_back(s.at(i));
        if(s.at(i)==' ')    razmak=true;
        else if(razmak) {
            brojac++;
            razmak=false;
        }
        if(!zavrseno && brojac==n)
        {
            s.insert(i,1,'(');
            while(i<s.length() && s.at(i)!=' ') i++;
            s.insert(i,1,')');
            zavrseno=true;
        }
    }
    if(n<1 || n>brojac) throw std::range_error("Nekorektan redni broj rijeci");
    return brojac;
}
int main()
{
    std::cout<<"Unesite string: ";
    std::string s;
    std::getline(std::cin,s);
    std::cout<<"Redni broj rijeci: ";
    int n;
    std::cin>>n;
    try {
        auto br=OgradiRijec(s,n);
        std::cout<<s;
        std::cout<<"\nBroj rijeci: "<<br;
    } catch (std::range_error e) {
        std::cout<<"\nNema toliko rijeci!";
    }
    return 0;
}
