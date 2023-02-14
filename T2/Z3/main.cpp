//TP 2018/2019: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>
using std::cin;
using std::cout;
int main ()
{
    cout<<"Unesite broj elemenata: "<<std::endl;
    int n;
    cin>>n;
    std::complex<double> suma {0,0};
    for(int i=0;i<n;i++)
    {
        std::complex<double> z;
        cout<<"Z_"<<i+1<<" = ";
        cin>>z;
        
        suma+=1./z;
    }
    cout<<std::endl<<"Paralelna veza ovih elemenata ima impedansu Z_ = "<<1./suma<<".";
	return 0;
}