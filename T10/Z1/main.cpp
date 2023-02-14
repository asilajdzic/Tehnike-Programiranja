#include <iostream>
#include <stdexcept>
class StedniRacun
{
	double stanjeRacuna;
public:
	StedniRacun()
	{
		stanjeRacuna=0;
	}
	StedniRacun(double pocetnoStanje);
	void Ulozi(double iznos)
	{
		if(iznos<0 && iznos*-1>stanjeRacuna)	throw std::logic_error("Transakcija odbijena");
		stanjeRacuna+=iznos;
	}
	void Podigni(double iznos);
	double DajStanje () const
	{
		return stanjeRacuna;
	}
	void ObracunajKamatu(double kamatnaStopa);
};
StedniRacun::StedniRacun(double pocetnoStanje)
{
	if(pocetnoStanje<0)  throw std::logic_error("Nedozvoljeno pocetno stanje");
	else stanjeRacuna=pocetnoStanje;
}
void StedniRacun::Podigni(double iznos)
{
	if(iznos>stanjeRacuna) throw std::logic_error("Transakcija odbijena");
	else stanjeRacuna-=iznos;
}
void StedniRacun::ObracunajKamatu(double kamatnaStopa)
{
	if(kamatnaStopa<=0) throw std::logic_error("Nedozvoljena kamatna stopa");
	else stanjeRacuna+=stanjeRacuna*kamatnaStopa/100.;
}
int main ()
{
	try {
		StedniRacun racun(100);
		racun.Ulozi(750);
		racun.Podigni(150);
		racun.ObracunajKamatu(17);
		std::cout<<racun.DajStanje();
	} catch(std::logic_error e) {
		std::cout<<e.what();
	}
	return 0;
}
