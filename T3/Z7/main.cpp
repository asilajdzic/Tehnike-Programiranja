//TP 2018/2019: Tutorijal 3, Zadatak 7
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
typedef std::vector<std::vector<int>> matrica;
using std::cin;
using std::cout;
int NajvecaSirina(matrica c)
{
    int max_sirina=0;
    for(int i=0;i<c.size();i++)
    {
        for(int j=0;j<c[i].size();j++)
        {
            long int tmp=c[i][j];
            int sirina=0;
            if(tmp<0)
            {
                sirina++;
                tmp*=-1;
            }
            while(tmp>0)
            {
                sirina++;
                tmp/=10;
            }
            if(sirina>max_sirina)
            max_sirina=sirina;
        }
    }
    return max_sirina;
}
matrica PascalovTrougao (int n)
{
    if(n<0)
    {
        throw std::domain_error("Broj redova ne smije biti negativan");
    }
    matrica izlaz(n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i+1;j++)
        {
           if(i==j || j==0)
           izlaz[i].push_back(1);
           else 
           izlaz[i].push_back(izlaz[i-1][j]+izlaz[i-1][j-1]);
        }
    }
    return izlaz;
}
int main ()
{
    cout<<"Unesite broj redova: \n";
    int n;
    cin>>n;
    auto m=PascalovTrougao(n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i+1;j++)
        cout<<std::setw(NajvecaSirina(m)+1)<<m[i][j];
        cout<<"\n";
    }
	return 0;
}