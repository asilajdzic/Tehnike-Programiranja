/*
    TP 16/17 (Tutorijal 7, Zadatak 6)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <list>
template<typename tip>
void SortirajListu (std::list<tip> &lista)
{
	for(auto it1=lista.begin(); it1!=lista.end(); it1++) {
		tip x=*it1;
		for(auto it2=it1; it2!=lista.end(); it2++) {
			if(*it2<x) {
				x=*it2;
				*it2=*it1;
				*it1=x;
			}
		}
	}
}
int main ()
{
	std::cout<<"Koliko ima elemenata: ";
	int n;
	std::cin>>n;
	std::list<int> lista;
	std::cout<<"Unesite elemente: ";
	for(int i=0; i<n; i++) {
		int x;
		std::cin>>x;
		lista.push_back(x);
	}
	std::cout<<"Sortirana lista: ";
	SortirajListu(lista);
	for(int x : lista) std::cout<<x<<" ";
	return 0;
}