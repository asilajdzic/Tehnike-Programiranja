/*
    TP 2018/2019: Tutorijal 5, Zadatak 5

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
#include <cmath>
#include <iomanip>
using std::cout;
using std::cin;
int BrojCifara (int n)
{
	if(!n)
	return 1;
	return int(log10(std::abs(n)))+1;
}
double TrapeznoPravilo (double (*f)(double),double a, double b,int n)
{
	double suma=0;
	for(int k=1; k<n; k++) {
		suma+=f(a+((b-a)/n)*k);;
	}
	double izlaz= (b-a)/n * (0.5*f(a) + 0.5*f(b) + suma);
	if(izlaz<=1e-10)
	return 0;
	return izlaz;
}
int main ()
{
	const double pi=4*atan(1);
	int n;
	cout<<"Unesite broj podintervala: ";
	cin>>n;
	double f1=TrapeznoPravilo(sin,0,pi,n);
	double f2=TrapeznoPravilo([](double x)-> double{return x*x*x;},0,10,n);
	double f3=TrapeznoPravilo([](double x)-> double{return 1/x;},1,2,n);
	cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose:\n";
	cout<<"- Za funkciju sin x na intervalu (0,pi): "<<std::setprecision(6-BrojCifara(f1))<<std::fixed<<f1<<std::endl;
	cout<<"- Za funkciju x^3 na intervalu (0,10): "<<std::setprecision(6-BrojCifara(f2))<<std::fixed<<f2<<std::endl;
	cout<<"- Za funkciju 1/x na intervalu (1,2): "<<std::setprecision(6-BrojCifara(f3))<<std::fixed<<f3;
	return 0;
}
