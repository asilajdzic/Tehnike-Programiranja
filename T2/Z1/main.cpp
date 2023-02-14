//TP 2018/2019: Tutorijal 2, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>
using std::cout;
using std::cin;
bool DaLiJeProst (int n)
{
    if(n<=1)
        return false;
    for(int i=2; i<=sqrt(n); i++)
        if(n%i==0) return false;
    return true;
}
std::vector<int> ProstiBrojeviUOpsegu (long int a,long int b)
{
    std::vector<int> prosti_br;
    for(long int i=a; i<=b; i++)  {
        if(DaLiJeProst(i))
            prosti_br.push_back(i);
    }
    return prosti_br;
}
int main ()
{
    cout<<"Unesite pocetnu i krajnju vrijednost: ";
    int a,b;
    cin>>a>>b;
    std::vector<int> prosti_br=ProstiBrojeviUOpsegu(a,b);
    if(prosti_br.size()) {
        cout<<"Prosti brojevi u rasponu od "<<a<<" do "<<b<<" su: ";
        for(int i=0; i<prosti_br.size(); i++)
            if(i<prosti_br.size()-1)
                cout<<prosti_br[i]<<", ";
            else
                cout<<prosti_br[i]<<std::endl;
    } else cout<<"Nema prostih brojeva u rasponu od "<<a<<" do "<<b<<"!";
    return 0;
}
