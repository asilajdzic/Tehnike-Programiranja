/*
    TP 16/17 (Tutorijal 7, Zadatak 3)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
/*
bool KriterijZaSort(std::string s1, std::string s2)
{
	if(s1<=s2) return true;
	return false;
}
int main ()
{
	try {
		int n;
		std::cout<<"Koliko zelite recenica: ";
		std::cin>>n;
		std::cout<<"Unesite recenice:\n";
		std::cin.ignore(100000,'\n');
		auto nizRecenica=new std::string[n];
		for(int i=0; i<n; i++) {
			try {
				std::getline(std::cin,nizRecenica[i]);
			} catch(...) {
				delete[] nizRecenica;
			}

		}
		std::sort(nizRecenica,nizRecenica+n,KriterijZaSort);
		std::cout<<"Sortirane recenice:\n";
		for(int i=0; i<n; i++)
			std::cout<<nizRecenica[i]<<"\n";
		delete[] nizRecenica;
		return 0;
	} catch(...) {
		std::cout<<"Problemi s memorijom!";
	}
}
*/
bool Sortiranje (std::string *s1, std::string *s2)
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
		auto nizRecenica=new std::string*[n];
		for(int i=0; i<n; i++) {
			try {
				nizRecenica[i]=new std::string;
				std::getline(std::cin,*nizRecenica[i]);
			} catch(...) {
				for(int i=0; i<n; i++) delete nizRecenica[i];
				delete[] nizRecenica;
				throw;
			}
		}
		std::sort(nizRecenica,nizRecenica+n,Sortiranje);
		std::cout<<"Sortirane recenice:\n";
		for(int i=0; i<n; i++)
			std::cout<<*nizRecenica[i]<<"\n";
		for(int i=0; i<n; i++)	delete nizRecenica[i];
		delete[] nizRecenica;
		return 0;
	} catch(...) {
		std::cout<<"Problemi s memorijom!";
	}
}
