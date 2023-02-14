//TP 2018/2019: Tutorijal 2, Zadatak 5
#include <iostream>
#include <complex>
const double PI=4*atan(1);
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
        double z,fi;
        cout<<"Z"<<i+1<<" = ";
        cin>>z;
        cout<<"fi"<<i+1<<" = "<<std::endl;
        cin>>fi;
        fi=fi*PI/180;
        std::complex<double> Z=std::polar(z,fi);
        
        suma+=1./Z;
    }
    cout<<"Paralelna veza ovih elemenata ima Z = "<<std::abs(1./suma)<<" i fi = "<<arg(1./suma)*180/PI<<".";
	return 0;
}