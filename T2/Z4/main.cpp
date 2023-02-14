//TP 2018/2019: Tutorijal 2, Zadatak 4
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
        double r,x;
        cout<<"R"<<i+1<<" = ";
        cin>>r;
        cout<<"X"<<i+1<<" = "<<std::endl;
        cin>>x;
        std::complex<double> z(r,x);
        suma+=1./z;
    }
    suma=1./suma;
    cout<<"Paralelna veza ovih elemenata ima R = "<<suma.real()<<" i X = "<<suma.imag()<<".";
	return 0;
}