/*
    TP 16/17 (Tutorijal 11, Zadatak 4)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <cstring>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <memory>
class Tim
{
	char ime_tima[20];
	int broj_odigranih;
	int broj_pobjeda;
	int broj_nerijesenih;
	int broj_poraza;
	int broj_datih;
	int broj_primljenih;
	int broj_poena;
public:
	Tim(const char ime[]);
	void ObradiUtakmicu(int broj_datih, int broj_primljenih);
	const char *DajImeTima() const
	{
		return ime_tima;
	}
	int DajBrojPoena() const
	{
		return broj_poena;
	}
	int DajGolRazliku() const
	{
		return (broj_datih-broj_primljenih);
	}
	void IspisiPodatke() const;
};
Tim::Tim(const char ime[])
{
	if(strlen(ime)>20) throw std::range_error("Predugacko ime tima");
	strcpy(ime_tima, ime);
	broj_datih=0;
	broj_odigranih=0;
	broj_pobjeda=0;
	broj_poena=0;
	broj_poraza=0;
	broj_primljenih=0;
	broj_datih=0;
	broj_nerijesenih=0;
}
void Tim::ObradiUtakmicu(int broj_datih, int broj_primljenih)
{
	if(broj_datih<0 || broj_primljenih<0)	throw std::range_error("Neispravan broj golova");
	Tim::broj_odigranih++;
	Tim::broj_datih+=broj_datih;
	Tim::broj_primljenih+=broj_primljenih;
	if(broj_datih>broj_primljenih) {
		Tim::broj_pobjeda++;
		Tim::broj_poena+=3;
	} else if(broj_primljenih==broj_datih) {
		Tim::broj_poena++;
		Tim::broj_nerijesenih++;
	} else
		Tim::broj_poraza++;
}
void Tim::IspisiPodatke() const
{
	std::cout<<std::setw(20)<<std::left<<ime_tima<<std::setw(4)<<std::right<<broj_odigranih<<std::setw(4)<<std::right<<broj_pobjeda
	         <<std::setw(4)<<std::right<<broj_nerijesenih<<std::setw(4)<<std::right<<broj_poraza<<std::setw(4)<<std::right<<broj_datih
	         <<std::setw(4)<<std::right<<broj_primljenih<<std::setw(4)<<std::right<<broj_poena<<std::endl;
}
bool SortKriterij(std::shared_ptr<Tim> tim1, std::shared_ptr<Tim> tim2)
{
	if(tim1->DajBrojPoena()==tim2->DajBrojPoena()) {
		if(tim1->DajGolRazliku()>tim2->DajGolRazliku()) return true;
		else if(tim1->DajGolRazliku()<tim2->DajGolRazliku()) return false;
		else {
			if(strcmp(tim1->DajImeTima(),tim2->DajImeTima())<0) return true;
			else return false;
		}
	}
	return (tim1->DajBrojPoena()>tim2->DajBrojPoena());
}
class Liga
{
	std::vector<std::shared_ptr<Tim>> timovi;
public:
	explicit Liga() {}
	explicit Liga(std::initializer_list<Tim> lista_timova);
	Liga(const Liga &l);
	Liga(Liga &&l);
	Liga &operator = (const Liga &l)
	{
		timovi=l.timovi;
		return *this;
	}
	Liga &operator = (Liga &&l)
	{
		timovi=l.timovi;
		l.timovi.resize(0);
		return *this;
	}
	void DodajNoviTim(const char ime_tima[]);
	void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2);
	void IspisiTabelu();
};
Liga::Liga(std::initializer_list<Tim> lista_timova)
{
	timovi.resize(lista_timova.size());
	auto it=lista_timova.begin();
	for(int i=0; i<lista_timova.size(); i++) {
		timovi[i]=std::make_shared<Tim>(it->DajImeTima());
		it++;
	}
}
Liga::Liga(const Liga &l)
{
	timovi.resize(l.timovi.size());
	for(int i=0; i<l.timovi.size(); i++)
		timovi[i]=std::make_shared<Tim>(*l.timovi[i]);

}
Liga::Liga(Liga &&l)
{
	timovi.resize(l.timovi.size());
	for(int i=0; i<l.timovi.size(); i++)
		timovi[i]=std::make_shared<Tim>(*l.timovi[i]);
	l.timovi.resize(0);
}
void Liga::DodajNoviTim(const char ime_tima[])
{
	timovi.push_back(std::make_shared<Tim>(ime_tima));
}
void Liga::RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2)
{
	bool postoji_prvi_tim=false,postoji_drugi_tim=false;
	int mjesto1, mjesto2;
	for(int i=0; i<timovi.size(); i++) {
		if(strcmp(timovi[i]->DajImeTima(),tim1)==0) {
			postoji_prvi_tim=true;
			mjesto1=i;
		}
		if(strcmp(timovi[i]->DajImeTima(),tim2)==0) {
			postoji_drugi_tim=true;
			mjesto2=i;
		}
	}
	if(!postoji_prvi_tim || !postoji_drugi_tim)	throw std::logic_error("Tim nije nadjen");
	timovi[mjesto1]->ObradiUtakmicu(rezultat_1,rezultat_2);
	timovi[mjesto2]->ObradiUtakmicu(rezultat_2,rezultat_1);
}
void Liga::IspisiTabelu()
{
	std::sort(timovi.begin(),timovi.end(),SortKriterij);
	for(int i=0; i<timovi.size(); i++)
		timovi[i]->IspisiPodatke();
}
int main ()
{
	Liga PLBiH{"Sarajevo","svinjski","seljo"};
	for(;;) {
		PLBiH.IspisiTabelu();
		char tim1[20],tim2[20];
		int br_gol1,br_gol2;
		std::cout<<"Unesite ime prvog tima (ENTER za kraj): ";
		std::cin.getline(tim1,sizeof(tim1));
		std::cout<<"Unesite ime drugog tima (ENTER za kraj): ";
		std::cin.getline(tim2,sizeof(tim2));
		std::cout<<"Unesite broj postignutih golova za oba tima: ";
		std::cin>>br_gol1>>br_gol2;
		std::cin.ignore(10000,'\n');
		PLBiH.RegistrirajUtakmicu(tim1,tim2,br_gol1,br_gol2);
	}
	return 0;
}