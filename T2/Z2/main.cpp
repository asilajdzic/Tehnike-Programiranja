//TP 2018/2019: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;
bool TestPerioda (vector<double> v, int p)  {
    if(p>=v.size() || p==0)
    return false;
    for(int i=0;i+p<v.size();i++)
    {
    if(v[i]!=v[i+p])
    return false;
    }
    return true;
}
int OdrediOsnovniPeriod (vector<double> v)  {
    for(int i=1;i<v.size();i++)
    {
    if(TestPerioda(v,i))
    return i;
    }
    return 0;
}
int main ()
{
    cout<<"Unesite slijed brojeva (0 za kraj): ";
    vector<double> v;
    double a;
    for(;;)
    {
        cin>>a;
        if(!a)
        break;
        v.push_back(a);
    }
    if(OdrediOsnovniPeriod(v))
    cout<<"Slijed je periodican sa osnovnim periodom "<<OdrediOsnovniPeriod(v)<<".";
    else 
    cout<<"Slijed nije periodican!";
	return 0;
}