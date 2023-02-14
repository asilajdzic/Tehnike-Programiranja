/*
    TP 2018/2019: Tutorijal 5, Zadatak 3

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
#include <algorithm>
#include <cmath>
using std::cout;
using std::cin;
void Unos(int &n)
{
	cin>>n;
}
bool PotpuniKvadrat (int n)
{
	return std::sqrt(n)-floor(std::sqrt(n))==0;
}
int Cifara(int n)
{
	if(n==0)
		return 1;
	return int(log10(std::abs(n)))+1;
}
bool JeLiTrocifren (int n)
{
	if(abs(n)>99 && abs(n)<1000)
		return true;
	return false;
}
int main ()
{
	cout<<"Unesite broj elemenata (max. 1000): ";
	int n;
	cin>>n;
	cout<<"Unesite elemente: ";
	int niz[1000];
	std::for_each(&niz[0],&niz[n],Unos);
	cout<<"Najveci element niza je "<<*std::max_element(&niz[0],&niz[n])<<std::endl;
	cout<<"Najmanji element niza se pojavljuje "<<std::count(&niz[0],&niz[n],*std::min_element(&niz[0],&niz[n]))<<" puta u nizu"<<std::endl;
	cout<<"U nizu ima "<<std::count_if(&niz[0],&niz[n],PotpuniKvadrat)<<" brojeva koji su potpuni kvadrati"<<std::endl;
	auto najmanji=*std::min_element(&niz[0],&niz[n]);
	int brojCifara[1000];
	std::transform(&niz[0],&niz[n],&brojCifara[0],Cifara);
	int* tmp=brojCifara;
	int indeks_prvog=std::min_element(&brojCifara[0],&brojCifara[n])-tmp;
	cout<<"Prvi element sa najmanjim brojem cifara je "<<niz[indeks_prvog]<<std::endl;
	auto kraj=std::remove_if(&niz[0],&niz[n],JeLiTrocifren);
	cout<<"Elementi koji nisu trocifreni su:";
	int* poc=niz;
	while(poc!=kraj) {
		cout<<" "<<*poc;
		poc++;
	}
	return 0;
}
