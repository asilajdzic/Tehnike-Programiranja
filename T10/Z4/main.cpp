#include <iostream>
#include <cmath>
#define PI 4*atan(1)
#include <iomanip>
int BrojSekundi(double x)
{
	return (x*180*60*60)/(PI);
}
class Ugao
{
	double ugao;
public:
	Ugao(double radijani = 0);
	Ugao(int stepeni, int minute, int sekunde);
	void Postavi(double radijani);
	void Postavi(int stepeni, int minute, int sekunde);
	double DajRadijane() const
	{
		return ugao;
	}
	void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde);
	int DajStepene() const;
	int DajMinute() const;
	int DajSekunde() const;
	void Ispisi() const
	{
		std::cout<<std::fixed<<std::setprecision(5)<<DajRadijane();
	}
	void IspisiKlasicno() const
	{
		std::cout<<std::fixed<<std::setprecision(5)<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec";
	}
	Ugao &SaberiSa(const Ugao &u);
	Ugao &PomnoziSa(double x);
	friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
	friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);

};
Ugao::Ugao(double radijani)
{
	Postavi(radijani);
}
Ugao::Ugao(int stepeni, int minute, int sekunde)
{
	Postavi((stepeni+minute/60.+sekunde/3600.)*PI/180.);
}
void Ugao::Postavi(double radijani)
{
	while(radijani>=2*PI) radijani-=2*PI;
	while(radijani<0)	radijani+=2*PI;
	ugao=radijani;
}
void Ugao::Postavi(int stepeni, int minute, int sekunde)
{
	Postavi((stepeni+minute/60.+sekunde/3600.)*PI/180.);
}
void Ugao::OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde)
{
	stepeni=ugao*180/PI;
	minute=ugao*3/PI;
	sekunde=ugao/(20*PI);
}
Ugao &Ugao::SaberiSa(const Ugao &u)
{
	Postavi(DajRadijane()+u.DajRadijane()+0.00000005);
	return *this;
}
Ugao &Ugao::PomnoziSa(double x)
{
	Postavi(ugao*x);
	return *this;
}
int Ugao::DajStepene() const
{
	return BrojSekundi(ugao)/3600;
}
int Ugao::DajMinute() const
{
	return (BrojSekundi(ugao)/60)%60;
}
int Ugao::DajSekunde() const
{
	return BrojSekundi(ugao)%60;
}
Ugao ZbirUglova(const Ugao &u1, const Ugao &u2)
{
	double zbir=u1.DajRadijane()+u2.DajRadijane();
	while(zbir<0) zbir+=2*PI;
	while(zbir>=2*PI) zbir-=2*PI;
	return zbir;
}
Ugao ProduktUglaSaBrojem(const Ugao &u, double x)
{
	double proizvod=u.DajRadijane()*x;
	while(proizvod<0) proizvod+=2*PI;
	while(proizvod>=2*PI) proizvod-=2*PI;
	return proizvod;
}
int main()
{
	Ugao u(50, 25, 12), v(500, 300, 200), f(50, 30, 10);
	u.SaberiSa(f);
	u.IspisiKlasicno();
	std::cout << std::endl;
	u.SaberiSa(v);
	u.IspisiKlasicno();
	std::cout << std::endl;
	return 0;
}
