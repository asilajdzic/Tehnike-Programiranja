/*
    TP 16/17 (Tutorijal 7, Zadatak 10)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <functional>
std::function<int(int)>PomocnaFunkcija(std::function<int(int)> f1, std::function<int(int)>f2)
{
	return[f1,f2](int x){
	return f2(f1(x));	
	};
}
std::function<int(int)>IteriranaFunkcija(int (f) (int),int n)
{
	if(n<=0) return [](int x){return x;};
	if(n==1) return[f](int x){return f(x);};
	auto izlaz=PomocnaFunkcija(f,f);
	while(n>2) {
		izlaz=PomocnaFunkcija(f,izlaz);
		n--;
	}
	return izlaz;
}
int main ()
{
	return 0;
}
