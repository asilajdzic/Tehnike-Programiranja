/*
    TP 2018/2019: Tutorijal 5, Zadatak 6

	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.

	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.

			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
int SumaCifara(int n)
{
	if(n==0) {
		return 0;
	}
	return(std::abs(n%10)+SumaCifara(std::abs(n/10)));
}
bool PorediCifre (int a, int b)
{
	if(SumaCifara(a)==SumaCifara(b))
	return b>a;
	return SumaCifara(a)<SumaCifara(b);
}
int main ()
{
	cout<<"Unesite broj elemenata: ";
	int n;
	cin>>n;
	cout<<"Unesite elemente: ";
	std::vector<int> v(n);
	std::for_each(v.begin(),v.end(), [](int &x){std::cin>>x;});
	std::sort(v.begin(),v.end(),PorediCifre);
	cout<<"Niz sortiran po sumi cifara glasi:";
	std::for_each(v.begin(),v.end(), [](int &x){std::cout<<" "<<x;});
	cout<<"\nUnesite broj koji trazite: ";
	int x;
	cin>>x;
	auto tmp=std::find(v.begin(),v.end(),x);
	if(tmp==v.end())
	cout<<"Trazeni broj ne nalazi se u nizu!";
	else 
	cout<<"Trazeni broj nalazi se na poziciji "<<tmp-v.begin();
	    return 0;
}
