/*
    TP 2018/2019: Tutorijal 6, Zadatak 2

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include <vector>
#include <stdexcept>
#include <type_traits>
template<typename itTip>
auto KreirajIzvrnutiNiz(itTip poc,itTip kraj) -> typename std::remove_reference<decltype(*poc)>::type*
{
	auto adresa=poc;
	int duzina=0;
	while(adresa!=kraj) {
		adresa++;
		duzina++;
	}
	auto izvrnuti=new typename std::remove_reference<decltype(*poc)>::type[duzina];
	for(int i=0; i<duzina; i++)
		izvrnuti[duzina-1-i]=*poc++;
	return izvrnuti;
}
int main ()
{
	try {
		int n;
		std::cout<<"Koliko zelite elemenata: ";
		std::cin>>n;
		std::vector<double> v(n);
		std::cout<<"Unesite elemente: ";
		for(int i=0; i<n; i++)
			std::cin>>v.at(i);
		double *p=KreirajIzvrnutiNiz(v.begin(),v.end());
		std::cout<<"Kreirani niz:";
		for(int i=0; i<n; i++)
			std::cout<<" "<<p[i];
		delete[] p;

	} catch(...) {
		std::cout<<"Nedovoljno memorije!";
	}
	return 0;
}
