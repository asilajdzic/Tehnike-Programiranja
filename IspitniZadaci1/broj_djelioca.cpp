#include <iostream>
#include <cmath>

int BrojDjelioca(int n)
{
    int brojac=0;
    for(int i=1; i<=sqrt(n); i++) {
        if(n%i==0) {
            if(n/i==i) brojac++;
            else brojac+=2;
        }
    }
    return brojac;
}

int main()
{
    int n;
    std::cin>>n;
    std::cout<<BrojDjelioca(n);
}
