//TP 2016/2017: Tutorijal 1, Zadatak 1
#include <iostream>
#include <cmath>
int main ()
{
    int a,b,c;
    std::cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    std::cin>>a>>b>>c;
    int d;
    std::cout<<"Unesite sirinu plocice u centimetrima: "<<std::endl;
    std::cin>>d;
    a=a*100;
    b=b*100;
    c=c*100;
    int suma=0;
    suma+=a*b;
    suma+=2*a*c;
    suma+=2*b*c;
    //if((a*b)%(d*d) || (a*c)%(d*d) || (c*b)%(d*d))
    //if(suma%(d*d))
    if(a%d || b%d || c%d)
    std::cout<<"Poplocavanje bazena dimenzija "<<a/100<<"x"<<b/100<<"x"<<c/100<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<std::endl<<"nije izvodljivo bez lomljenja plocica!";
    else 
    std::cout<<"Za poplocavanje bazena dimenzija "<<a/100<<"x"<<b/100<<"x"<<c/100<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<std::endl<<"potrebno je "<<suma/(d*d)<<" plocica.";
	return 0;
}