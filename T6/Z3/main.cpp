/*
    TP 2018/2019: Tutorijal 6, Zadatak 3

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include <stdexcept>
int **KreirajTrougao(int n)
{
	if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
	try {
		int **red=new int*[n];
		for(int i=0; i<n; i++) {
			try {
				int duzina=2*i+1;
				red[i]=new int[duzina];
				for(int j=0; j<=duzina/2; j++) {
					red[i][j]=i+1-j;
					red[i][duzina-1-j]=i+1-j;
				}
			} catch (std::bad_alloc) {
				for(int i=0; i<n; i++)
					delete[] red[i];
				delete[] red;
				throw;
			}
		}
		return red;
	} catch (std::bad_alloc) {
		throw;
	}
}
int main ()
{
	try {
		std::cout<<"Koliko zelite redova: ";
		int n;
		std::cin>>n;
		auto trougao=KreirajTrougao(n);
		for(int i=0; i<n; i++) {
			for(int j=0; j<2*i+1; j++) {
				std::cout<<trougao[i][j]<<" ";
			}
			delete[] trougao[i];
			std::cout<<"\n";
		}
		delete[] trougao;
	} catch(std::bad_alloc) {
		std::cout<<"Izuzetak: Nedovoljno memorije!";
	} catch(std::domain_error e) {
		std::cout<<"Izuzetak: "<<e.what();
	}
	return 0;
}