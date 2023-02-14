/* 
    TP 16/17 (Tutorijal 7, Zadatak 8)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <algorithm>
std::string IzvrniBezRazmaka (std::string s)
{
	std::string izlaz;
	std::remove_copy(s.rbegin(),s.rend(),back_inserter(izlaz),' ');
	return izlaz;
}
int main ()
{
	std::string s{"Izvrni ovaj string "};
	std::cout<<s<<"\n"<<IzvrniBezRazmaka(s);
	return 0;
}