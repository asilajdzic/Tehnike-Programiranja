/* 
    TP 16/17 (Tutorijal 7, Zadatak 2)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
bool KriterijZaSort(char* s1, char *s2)
{
	if(strcmp(s1,s2)<0) return true;
	return false;
}
int main ()
{
	try{
		int n;
		std::cout<<"Koliko zelite recenica: ";
		std::cin>>n;
		std::cout<<"Unesite recenice:\n";
		std::cin.ignore(100000,'\n');
		char **nizRecenica(new char*[n]);
		for(int i=0;i<n;i++)
		{
			char recenica[1000];
			std::cin.getline(recenica,sizeof(recenica));
			try
			{
				nizRecenica[i]=new char[strlen(recenica)+1];
			}
			catch(...)
			{
				for(int i=0;i<n;i++) delete[] nizRecenica[i];
				delete[] nizRecenica;
				throw;
			}
			strcpy(nizRecenica[i],recenica);
		}
		std::sort(nizRecenica,nizRecenica+n,KriterijZaSort);
		std::cout<<"Sortirane recenice:\n";
		for(int i=0;i<n;i++)
		std::cout<<nizRecenica[i]<<"\n";
		for(int i=0;i<n;i++) delete[] nizRecenica[i];
		delete[] nizRecenica;
		return 0;
	}
	catch(...)
	{
		std::cout<<"Problemi s memorijom!";
	}
}