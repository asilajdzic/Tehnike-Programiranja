#include <iostream>
#include <cmath>
#define PI 4*atan(1)
#include <iomanip>
int BrojSekundi(double x)
{
	return int((x*180*60*60)/(PI));
}
class Ugao
{
	int step, min, sek;
public:
	Ugao(double radijani = 0);
	Ugao(int stepeni, int minute, int sekunde);
	void Postavi(double radijani);
	void Postavi(int stepeni, int minute, int sekunde);
	double DajRadijane() const;
	void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde);
	int DajStepene() const
	{
		return step;
	}
	int DajMinute() const
	{
		return min;
	}
	int DajSekunde() const
	{
		return sek;
	}
	void Ispisi() const
	{
		std::cout<<std::fixed<<std::setprecision(5)<<DajRadijane();
	}
	void IspisiKlasicno() const
	{
		std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec";
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
	Postavi(stepeni,minute,sekunde);
}
void Ugao::Postavi(double radijani)
{
	Postavi(0,0,BrojSekundi(radijani));
}
void Ugao::Postavi(int stepeni, int minute, int sekunde)
{
	minute+=sekunde/60;
	stepeni+=minute/60;
	while(sekunde<0) {
		sekunde=60+sekunde;
		minute--;
	}
	sekunde=sekunde%60;
	minute=minute%60;
	while(minute<0) {
		minute=60+minute;
		stepeni--;
	}
	minute=minute%60;
	while(stepeni<0) stepeni=360+stepeni;
	stepeni=stepeni%360;
	step=stepeni;
	min=minute;
	sek=sekunde;
}
void Ugao::OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde)
{
	stepeni=step;
	minute=min;
	sekunde=sek;
}
double Ugao::DajRadijane() const
{
	double radijani=(DajStepene()*2*PI)/360+(DajMinute()*2*PI)/(360*60)+(DajSekunde()*2*PI)/(360*3600);
	while(radijani<0) radijani+=2*PI;
	while(radijani>=2*PI) radijani-=2*PI;
	return radijani;
}
Ugao &Ugao::SaberiSa(const Ugao &u)
{
	Postavi(DajRadijane()+u.DajRadijane()+0.00000005);
	return *this;
}
Ugao &Ugao::PomnoziSa(double x)
{
	Postavi(DajRadijane()*x);
	return *this;
}
Ugao ZbirUglova(const Ugao &u1, const Ugao &u2)
{
	double zbir=u1.DajRadijane()+u2.DajRadijane()+0.00000005;
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
	Ugao u,v;
	u.Postavi(212, 57, 28.062), v.Postavi(1,1,-1);
	u.Ispisi();
	std::cout << std::endl;
	u.IspisiKlasicno();
	std::cout << std::endl;
	v.Ispisi();
	v.IspisiKlasicno();
	std::cout << std::endl;
	Ugao z(90,0,0);
	z.IspisiKlasicno();
}
