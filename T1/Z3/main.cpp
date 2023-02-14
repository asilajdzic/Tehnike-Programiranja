//TP 2016/2017: Tutorijal 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <iomanip>
int main ()
{
    std::cout<<"Unesite pocetnu i krajnju vrijednost: "<<std::endl;
    int a,b;
    std::cin>>a>>b;
    std::cout<<"+---------+----------+----------+-----------+"<<std::endl;
    std::cout<<"| Brojevi | Kvadrati | Korijeni | Logaritmi |"<<std::endl;
    std::cout<<"+---------+----------+----------+-----------+"<<std::endl;
    for(int i=a;i<=b;i++)
    {
        std::cout<<"| ";
        std::cout.width(8);
        std::cout<<std::left<<i;
        std::cout<<"|";
        std::cout.width(9);
        std::cout<<std::right<<i*i;
        std::cout<<" |";
        std::cout.width(9);
        std::cout<<std::setprecision(3)<<std::fixed<<sqrt(i);
        std::cout<<" |";
        std::cout.width(10);
        std::cout<<std::setprecision(5)<<std::fixed<<log(i);
        std::cout<<" |"<<std::endl;
    }
    std::cout<<"+---------+----------+----------+-----------+";
	return 0;
}