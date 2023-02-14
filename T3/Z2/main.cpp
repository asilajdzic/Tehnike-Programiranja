#include <iostream>
#include <vector>
using std::cin;
using std::cout;
std::vector<int> IzdvojiElemente(std::vector<int> v,bool parni)
{
    std::vector<int> izlaz;
    for(int i=0;i<v.size();i++)
    {
        unsigned int tmp=abs(v[i]);
        int suma=0;
        while(tmp>0)
        {
            suma+=tmp%10;
            tmp/=10;
        }
        if(parni && suma%2==0)
        izlaz.push_back(v[i]);
        else if(!parni && suma%2==1)
        izlaz.push_back(v[i]);
    }
    return izlaz;
}
int main ()
{
    int n;
    cout<<"Koliko zelite unijeti elemenata: ";
    cin>>n;
    if(n<=0)
    {
        cout<<"Broj elemenata mora biti veci od 0!";
        return 0;
    }
    cout<<"Unesite elemente: ";
    int element;
    std::vector<int> a;
    for(int i=0; i<n; i++)
    {
        cin>>element;
        a.push_back(element);
    }
    std::vector<int> b=IzdvojiElemente(a,true);
    std::vector<int> c=IzdvojiElemente(a,false);
    for(int i=0; i<b.size(); i++)
        {
        if(i==b.size()-1)
        {
            cout<<b[i];
            break;
        }
        cout<<b[i]<<",";
        }
    cout<<"\n";
    for(int i=0; i<c.size(); i++)
        {
        if(i==c.size()-1)
        {
            cout<<c[i];
            break;
        }
        cout<<c[i]<<",";
        }
    return 0;
}