/* 
    TP 2018/2019: Tutorijal 5, Zadatak 1
	
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
using std::cout;
using std::cin;
void unesi(char niz[], int velicina) {
    char znak = getchar();
    if (znak == '\n') znak=getchar();
    char* vel=niz+velicina-1;
    while ( niz < vel && znak != '\n') {
        *niz = znak;
        niz++;
        znak = getchar();
    }
    *niz='\0';
}
int main ()
{
	cout<<"Unesite recenicu: ";
	char recenica[1000];
	unesi(recenica,1000);
	char* p=recenica;
	int br_rijeci=0;
	bool razmak=true;
	while (*p)
	{
		if(*p==' ')
		razmak=true;
		else if(razmak)
		{
			razmak=false;
			br_rijeci++;
		}
		if(br_rijeci==2)
		break;
		p++;
	}
	cout<<"Recenica bez prve rijeci glasi: ";
	while(*p)
	{
		cout<<*p;
		p++;
	}
	cout<<"\n";
	return 0;
}