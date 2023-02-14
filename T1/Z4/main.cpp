//TP 2016/2017: Tutorijal 1, Zadatak 4
#include <iostream>
#include <cmath>
int main ()
{
    for(;;)
    {
        double n;
        std::cout<<"Unesite prirodan broj ili 0 za kraj: ";
        while(!(std::cin>>n))
        {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout<<"Niste unijeli prirodan broj!"<<std::endl;
        std::cout<<"Unesite prirodan broj ili 0 za kraj: ";
        }
        if(n==0)
        {
            std::cout<<"Dovidjenja!";
        break;
        }
        if(n<0 || n-(int)n!=0)
        {
        std::cout<<"Niste unijeli prirodan broj!"<<std::endl;
        continue;
        }
        int suma=0;
        for(int i=1;i<n;i++)
            {
                if(((int)n%i)==0)
                suma+=i;
            }
        if(suma<n)
        std::cout<<"Broj "<<n<<" je manjkav!"<<std::endl;
        if(suma>n)
        std::cout<<"Broj "<<n<<" je obilan!"<<std::endl;
        if(suma==n)
        std::cout<<"Broj "<<n<<" je savrsen!"<<std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
        
	return 0;
}