/*
    TP 2018/2019: Tutorijal 5, Zadatak 2

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
template<typename Kolekcija1,typename Kolekcija2>
Kolekcija2 RazmijeniBlokove(Kolekcija1 poc1,Kolekcija1 kraj1,Kolekcija2 poc2) {
	while(poc1!=kraj1)
		{
			auto tmp=*poc1;
			*poc1=*poc2;
			*poc2=tmp;
			poc1++;
			poc2++;
		}
	return poc2;
}
int main ()
{
	return 0;
}