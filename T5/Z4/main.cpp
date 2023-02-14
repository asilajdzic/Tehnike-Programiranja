/* 
    TP 2018/2019: Tutorijal 5, Zadatak 4
	
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
#include <deque>
using std::cout;
using std::cin;
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
void Ispisi(int n)
{
	cout<<" "<<n;
}
int main ()
{
	cout<<"Unesite broj elemenata: ";
	int n;
	cin>>n;
	cout<<"Unesite elemente: ";
	std::deque<int>dek (n);
	for_each(dek.begin(),dek.end(),[](int &x){std::cin>>x;});
	cout<<"Najveci element deka je "<<*std::max_element(dek.begin(),dek.end())<<std::endl;
	cout<<"Najmanji element deka se pojavljuje "<<std::count(dek.begin(),dek.end(),*std::min_element(dek.begin(),dek.end()))<<" puta u deku"<<std::endl;
	cout<<"U deku ima "<<std::count_if(dek.begin(),dek.end(),PotpuniKvadrat)<<" brojeva koji su potpuni kvadrati"<<std::endl;
	auto najmanji=*std::min_element(dek.begin(),dek.end());
	std::deque<int> brojCifara(n);
	std::transform(dek.begin(),dek.end(),brojCifara.begin(),Cifara);
	auto poc=brojCifara.begin();
	auto kraj1=std::find(brojCifara.begin(), brojCifara.end(), *std::min_element(brojCifara.begin(),brojCifara.end()));
	cout<<"Prvi element sa najmanjim brojem cifara je "<<dek.at(kraj1-poc)<<std::endl;
	auto kraj2=std::remove_if(dek.begin(),dek.end(),JeLiTrocifren);
	cout<<"Elementi koji nisu trocifreni su:";
	std::for_each(dek.begin(),kraj2,Ispisi);
	return 0;
}