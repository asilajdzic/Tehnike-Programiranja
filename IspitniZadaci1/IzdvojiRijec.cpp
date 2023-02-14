#include <string>
#include <iostream>
#include <stdexcept>
#include <cctype>
std::string IzdvojiRijec(std::string s, int n)
{
    if(n<1) throw std::domain_error("Nepravilan redni broj rijeci!");
    std::string rijec;
    bool razmak=true;
    int broj_rijeci=0;
    for(int i=0; i<s.length(); i++) {
        if(s.at(i)==' ')
            razmak=true;
        else if(razmak) {
            ++broj_rijeci;
            razmak=false;
            while(i<s.length() && broj_rijeci==n && isalnum(s.at(i))) {
                rijec.push_back(s.at(i));
                i++;
            }
        }
    }
    if(broj_rijeci<n)   throw std::domain_error("Nepravilan redni broj rijeci!");
    return rijec;
}
int main()
{
    std::string s=" Riba ribi grize   rep    ";
    auto s2=IzdvojiRijec(s,3);
    std::cout<<s2;
    //i ovaj je malo ruzan ali radi, izgubio sam osjecaj za lijepo :(
    return 0;
}
