#include <iostream>
#include <stdexcept>
#include <iomanip>
class Sat
{
	int sekunde;
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
		Sat::sekunde=sati*3600+minute*60+sekunde;
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
		Sat::sekunde=sati*3600+minute*60+sekunde;
	}
	Sat &Sljedeci()
	{
		Sat::sekunde++;
		PostaviNormalizirano(DajSate(),DajMinute(),DajSekunde());
		return *this;
	}
	Sat &Prethodni()
	{
		Sat::sekunde--;
		PostaviNormalizirano(DajSate(),DajMinute(),DajSekunde());
		return *this;
	}
	Sat &PomjeriZa(int x)
	{
		while(x>0)
		{
			Sljedeci();
			x--;
		}
		while(x<0)
		{
			Prethodni();
			x++;
		}
		return *this;
	}
	void Ispisi()	const
	{
		std::cout<<std::setfill('0')<<std::setw(2)<<DajSate()<<":"<<std::setfill('0')<<std::setw(2)<<DajMinute()<<":"<<std::setfill('0')<<std::setw(2)<<DajSekunde();
	}
	int DajSate()	const
	{
		return Sat::sekunde/3600;
	}
	int DajMinute()	const
	{
		return (Sat::sekunde-DajSate()*3600)/60;
	}
	int DajSekunde()	const
	{
		return Sat::sekunde-DajSate()*3600-DajMinute()*60;
	}
	friend int BrojSekundiIzmedju(Sat s1, Sat s2);
	static int Razmak(Sat s1, Sat s2)
	{
		return s1.sekunde-s2.sekunde;
	}
};
int BrojSekundiIzmedju(Sat s1, Sat s2)
{
	return s1.sekunde-s2.sekunde;
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