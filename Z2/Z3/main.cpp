//TP 2018/2019: Zadaća 2, Zadatak 3
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>
int BrojCifara(long long int n)
{
    if(n==0)
        return 1;
    return int(log10(std::abs(n))+1);
}
int NajsiriBroj (long long int **grbavaMatrica, long long int n)
{
    if(n<0) throw std::domain_error("Parametar ne smije biti negativan");
    int max=0;
    for(long long int i=0; i<n+1; i++) {
        for(long long j=0; j<i+1; j++) {
            if(BrojCifara(grbavaMatrica[i][j])>max)
                max=BrojCifara(grbavaMatrica[i][j]);
        }
    }
    return max+1;
}
long long int StirlingovBroj(long long int i,long long int j)
{
    if(i==0 && j==0) return 1;
    if(i==0 && j!=0) return 0;
    if(i>j) return 0;
    return StirlingovBroj(i-1,j-1)+i*StirlingovBroj(i,j-1);
} //dobra
long long int **StirlingoviBrojeviF(long long int n)
{
    if(n<0) throw std::domain_error("Parametar ne smije biti negativan");
    long long int **grbavaMatrica=nullptr;
    try {
        grbavaMatrica=new long long int*[n+1];
        for(long long int i=0; i<n+1; i++)
            grbavaMatrica[i]=new long long int[i+1];
        for(long long int i=0; i<n+1; i++) {
            for(long long int j=0; j<i+1; j++) {
                grbavaMatrica[i][j]=StirlingovBroj(j,i);
            }
        }
        return grbavaMatrica;
    } catch(std::bad_alloc) {
        for(long long int i=0; i<n+1; i++)
            delete[] grbavaMatrica[i];
        delete[] grbavaMatrica;
        throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    }
} //dobra
long long int **StirlingoviBrojeviK(long long int n)
{
    if(n<0) throw std::domain_error("Parametar ne smije biti negativan");
    long long int duzina=(n+1)*(n+2)/2;
    long long int **grbavaMatrica=nullptr;
    try {
        grbavaMatrica=new long long int*[n+1];
        grbavaMatrica[0]=new long long int[duzina];
        for(long long int i=1; i<n+1; i++)
            grbavaMatrica[i]=grbavaMatrica[i-1]+i;
        for(long long int i=0; i<n+1; i++) {
            for(long long j=0; j<i+1; j++) {
                grbavaMatrica[i][j]=StirlingovBroj(j,i);
            }
        }
        return grbavaMatrica;
    } catch(std::bad_alloc) {
        delete[] grbavaMatrica;
        throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    }
} // dobra
int main ()
{
    try {
        std::cout<<"Unesite broj n: ";
        long long int n;
        std::cin>>n;
        auto fragmentiranaMatrica=StirlingoviBrojeviF(n);
        std::cout<<"\nStirlingovi brojevi - fragmentirana alokacija:\n";
        for(long long int i=0; i<n+1; i++) {
            for(long long int j=0; j<i+1; j++)
                std::cout<<std::setw(NajsiriBroj(fragmentiranaMatrica,n))<<std::right<<fragmentiranaMatrica[i][j];
            std::cout<<std::endl;
        }
        for(long long int i=0; i<n+1; i++)
            delete[] fragmentiranaMatrica[i];
        delete[] fragmentiranaMatrica;

        //___________________________________________________//
        auto kontinualnaMatrica=StirlingoviBrojeviK(n);
        std::cout<<"\nStirlingovi brojevi - kontinualna alokacija:\n";
        for(long long int i=0; i<n+1; i++) {
            for(long long int j=0; j<i+1; j++)
                std::cout<<std::setw(NajsiriBroj(kontinualnaMatrica,n))<<std::right<<kontinualnaMatrica[i][j];
            std::cout<<std::endl;
        }
        delete[] kontinualnaMatrica[0];
        delete[] kontinualnaMatrica;
    } catch (std::domain_error dp) {
        std::cout<<"Izuzetak: "<<dp.what()<<"!";
    } catch(std::range_error r) {
        std::cout<<"Izuzetak: "<<r.what()<<"!";
    }
    return 0;
}
