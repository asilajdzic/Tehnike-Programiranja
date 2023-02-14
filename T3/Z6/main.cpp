//TP 2018/2019: Tutorijal 3, Zadatak 6
#include <iostream>
#include <vector>
#include <iomanip>
using std::cin;
using std::cout;
typedef std::vector<std::vector<int>> matrica;
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
matrica KroneckerovProizvod (std::vector<int> a,std::vector<int> b)
{
    matrica izlaz(a.size(),std::vector<int>(b.size()));
    for(int i=0;i<a.size();i++)
    {
        for(int j=0;j<b.size();j++)
        izlaz[i][j]=a[i]*b[j];
    }
    return izlaz;
}
int main ()
{
    cout<<"Unesite broj elemenata prvog vektora: ";
    int n1;
    cin>>n1;
    std::vector<int> a(n1);
    cout<<"Unesite elemente prvog vektora: ";
    for(int i=0;i<n1;i++)
    cin>>a[i];
    cout<<"Unesite broj elemenata drugog vektora: ";
    int n2;
    cin>>n2;
    std::vector<int> b(n2);
    cout<<"Unesite elemente drugog vektora: \n";
    for(int i=0;i<n2;i++)
    cin>>b[i];
    auto c=KroneckerovProizvod(a,b);
    for(int i=0;i<c.size();i++)
    {
        for(int j=0;j<c[i].size();j++)
        {
            cout<<std::setw(NajvecaSirina(c)+1)<<c[i][j];
        }
        cout<<"\n";
    }
    
    
	return 0;
}