/*
    TP 2018/2019: Tutorijal 6, Zadatak 1

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include <stdexcept>
#include <limits>
template <typename tip>
tip *GenerirajStepeneDvojke (int n)
{
	if(n<=0)	throw std::domain_error ("Broj elemenata mora biti pozitivan");
	try {
		tip *p=new tip[n];
		for(int i=0; i<n; i++) {
			tip tmp=1;
			for(int j=1; j<=i; j++) {
				if(tmp*2>std::numeric_limits<tip>::max() || tmp*2<=0) {
					delete[] p;
					throw std::overflow_error("Prekoracen dozvoljeni opseg");
				}
				tmp*=2;
			}
			p[i]=tmp;
		}
		return p;
	} catch(std::bad_alloc) {
		throw std::runtime_error("Alokacija nije uspjela");
	}
}
int main ()
{
	std::cout<<"Koliko zelite elemenata: ";
	int n;
	std::cin>>n;
	try {
		long unsigned int *p=GenerirajStepeneDvojke<long unsigned int>(n);
		for(int i=0; i<n; i++)
			std::cout<<p[i]<<" ";
		delete[] p;
	} catch(std::domain_error dp) {
		std::cout<<"Izuzetak: "<<dp.what();
	} catch(std::runtime_error e) {
		std::cout<<"Izuzetak: "<<e.what();
	}
	//moze do n=64
	return 0;
}