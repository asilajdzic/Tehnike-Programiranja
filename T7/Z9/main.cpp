/*
    TP 16/17 (Tutorijal 7, Zadatak 9)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <functional>
std::function<double(double)> plus2(double x)
{
	return [x](double y) {
		return x+y;
	};
}
std::function<std::function<double(double)>(double)> plus3 (double x)
{
	return [x] (double y) {
		return[x,y](double z) {
			return x+y+z;
		};
	};
}
int main ()
{
	std::cout<<plus2(0.4)(0.2);
	std::cout<<"\n"<<plus3(0.2)(0.3)(0.1);
	return 0;
}
