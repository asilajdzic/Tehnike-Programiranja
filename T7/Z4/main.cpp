/*
    TP 16/17 (Tutorijal 7, Zadatak 4)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <memory>
typedef std::shared_ptr<std::string> dijeljeniPok;
bool Sortiranje (dijeljeniPok s1, dijeljeniPok s2)
{
	return *s1<*s2;
}
int main ()
{
	try {
		int n;
		std::cout<<"Koliko zelite recenica: ";
		std::cin>>n;
		std::cout<<"Unesite recenice:\n";
		std::cin.ignore(100000,'\n');
		std::unique_ptr<dijeljeniPok[]> nizRecenica(new dijeljeniPok[n]);
		for(int i=0; i<n; i++) {
			try {
				nizRecenica[i]=std::make_shared<std::string>();
				std::getline(std::cin,*nizRecenica[i]);
			} catch(...) {
				for(int i=0; i<n; i++) nizRecenica[i]=nullptr;
				nizRecenica=nullptr;
				throw;
			}
		}
		std::sort(nizRecenica.get(),nizRecenica.get()+n,Sortiranje);
		std::cout<<"Sortirane recenice:\n";
		for(int i=0; i<n; i++)
			std::cout<<*nizRecenica[i]<<"\n";
		for(int i=0; i<n; i++) nizRecenica[i]=nullptr;
		nizRecenica=nullptr;
		return 0;
	} catch(...) {
		std::cout<<"Problemi s memorijom!";
	}
}
