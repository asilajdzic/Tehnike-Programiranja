#include <iostream>
#include <stdexcept>
#include <iomanip>
class Sat
{
	int sati, minute, sekunde;
public:
	static bool DaLiJeIspravno(int sati, int minute, int sekunde)
	{
		if(sati<0 || sati>23 || minute<0 || minute>59 || sekunde<0 || sekunde>59)
			return false;
		return true;
	}
	void Postavi(int sati, int minute, int sekunde)
	{
		if(!DaLiJeIspravno(sati, minute, sekunde))
			throw std::domain_error("Neispravno vrijeme");
		Sat::sati=sati;
		Sat::minute=minute;
		Sat::sekunde=sekunde;
	}
	void PostaviNormalizirano(int sati, int minute, int sekunde)
	{
		minute+=sekunde/60;
		sati+=minute/60;
		sekunde=sekunde%60;
		if(sekunde<0) {
			sekunde=60+sekunde;
			minute--;
		}
		minute=minute%60;
		if(minute<0) {
			minute=60+minute;
			sati--;
		}
		sati=sati%24;
		if(sati<0) sati=24+sati;
		Sat::sati=sati;
		Sat::minute=minute;
		Sat::sekunde=sekunde;
	}
	Sat &Sljedeci()
	{
		Sat::sekunde++;
		Sat::minute+=Sat::sekunde/60;
		Sat::sekunde%=60;
		Sat::sati+=Sat::minute/60;
		Sat::sati%=24;
		Sat::minute%=60;
		return *this;
	}
	Sat &Prethodni()
	{
		Sat::sekunde--;
		if(Sat::sekunde<0) {
			minute--;
			sekunde=60+Sat::sekunde;
		}
		if(Sat::minute<0) {
			sati--;
			minute=60+Sat::minute;
		}
		Sat::minute+=Sat::sekunde/60;
		Sat::sekunde%=60;
		Sat::sati+=Sat::minute/60;
		Sat::sati%=24;
		Sat::minute%=60;
		if(Sat::sati<0)
			Sat::sati=24+Sat::sati;
		return *this;
	}
	Sat &PomjeriZa(int x)
	{
		Sat::sekunde+=x;
		if(Sat::sekunde<0) {
			minute--;
			sekunde=60+Sat::sekunde;
		}
		if(Sat::minute<0) {
			sati--;
			minute=60+Sat::minute;
		}
		Sat::minute+=Sat::sekunde/60;
		Sat::sekunde%=60;
		Sat::sati+=Sat::minute/60;
		Sat::sati%=24;
		Sat::minute%=60;
		if(Sat::sekunde<0) sekunde=60+Sat::sekunde;
		if(Sat::sati<0) Sat::sati+=24;
		return *this;
	}
	void Ispisi()	const
	{
		std::cout<<std::setfill('0')<<std::setw(2)<<Sat::sati<<":"<<std::setfill('0')<<std::setw(2)<<Sat::minute<<":"<<std::setfill('0')<<std::setw(2)<<Sat::sekunde;
	}
	int DajSate()	const
	{
		return Sat::sati;
	}
	int DajMinute()	const
	{
		return Sat::minute;
	}
	int DajSekunde()	const
	{
		return Sat::sekunde;
	}
	friend int BrojSekundiIzmedju(Sat s1, Sat s2);
	static int Razmak(Sat s1, Sat s2)
	{
		return (s1.DajSate()-s2.DajSate())*3600+(s1.DajMinute()-s2.DajMinute())*60 + s1.DajSekunde()-s2.DajSekunde();
	}
};
int BrojSekundiIzmedju(Sat s1, Sat s2)
{
	return (s1.DajSate()-s2.DajSate())*3600+(s1.DajMinute()-s2.DajMinute())*60 + s1.DajSekunde()-s2.DajSekunde();
}
int main ()
{
	Sat s;
	int sati=15, minute=-30, sekunde=0;
	s.PostaviNormalizirano(sati,minute, sekunde);
	s.Ispisi();
	std::cout<<"\n";
	s.Sljedeci().Ispisi();
	std::cout<<"\n";
	s.PomjeriZa(-5).Ispisi();
	std::cout<<"\n";
	return 0;
}
