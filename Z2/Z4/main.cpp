//TP 2018/2019: Zadaća 2, Zadatak 4
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
bool SortKriterij (std::string s1, std::string s2)
{
    if(s1.length()<s2.length())		return true;
    if(s1.length()==s2.length())  {
        for(int i=0; i<s1.length(); i++)
            s1.at(i)=std::toupper(s1.at(i));
        for(int i=0; i<s2.length(); i++)
            s2.at(i)=std::toupper(s2.at(i));
        return s1<s2;
    }
    return false;
}
void SortirajRecenice(std::string *poc,std::string *kraj)
{
    if(poc>kraj) throw std::domain_error("Nije moguce sortiranje");
    std::sort(poc,kraj,SortKriterij);
}
int main()
{
    try {
        std::cout<<"Unesite broj recenica: ";
        int n;
        std::cin>>n;
        std::cout<<"Unesite recenice: ";
        std::cin.ignore(1000,'\n');
        std::string *nizRecenica=nullptr;
        try {
            nizRecenica=new std::string[n];
            for(int i=0; i<n; i++)
                std::getline(std::cin,nizRecenica[i]);
        } catch(...) {
            delete[] nizRecenica;
            throw;
        }
        SortirajRecenice(nizRecenica,nizRecenica+n);
        std::cout<<"\nRecenice nakon sortiranja:";
        for(int i=0; i<n; i++)
            std::cout<<"\n"<<nizRecenica[i];
        std::cout<<"\n\nUnesite recenicu za pretragu: ";
        std::string rijec;
        std::getline(std::cin,rijec);
        if(std::binary_search(nizRecenica,nizRecenica+n,rijec,SortKriterij)) {
            std::cout<<"Recenica se nalazi na poziciji: "<<std::lower_bound(nizRecenica,nizRecenica+n,rijec,SortKriterij)-nizRecenica;
        } else
            std::cout<<"Trazena recenica se ne nalazi u nizu!";
        delete[] nizRecenica;
        return 0;
    } catch(...) {
        std::cout<<"Problemi s memorijom!";
    }
}
