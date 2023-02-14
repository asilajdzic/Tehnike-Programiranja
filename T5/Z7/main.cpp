/* 
    TP 2018/2019: Tutorijal 5, Zadatak 7
	
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
#include <algorithm>
#include <stdexcept>
#include <vector>
template <typename tipIt>
auto SumaBloka (tipIt p, tipIt q) ->decltype(*p+*p)
{
	if(p==q)
	throw std::range_error ("Blok je prazan");
	decltype(*p+*p) sumaBloka=*p++;
	while(p!=q)
	sumaBloka+=*p++;
	return sumaBloka;
}
int main ()
{
	return 0;
}