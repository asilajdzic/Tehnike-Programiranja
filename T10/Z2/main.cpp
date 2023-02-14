#include <iostream>
#include <cmath>
#include <iomanip>
class Krug
{
	double r;
public:
	explicit Krug(double rUnos);
	void Postavi(double rPostavi);
	double DajPoluprecnik() const
	{
		return r;
	}
	double DajObim() const
	{
		return 8*atan(1)*r;
	}
	double DajPovrsinu() const
	{
		return r*r*4*atan(1);
	}
	void Skaliraj(double skalar);
	void Ispisi() const;
};
Krug::Krug(double rUnos)
{
	if(rUnos<=0)	throw std::domain_error("Neispravan poluprecnik");
	else r=rUnos;
}
void Krug::Postavi(double rPostavi)
{
	if(rPostavi<=0)	throw std::domain_error("Neispravan poluprecnik");
	else r=rPostavi;
}
void Krug::Skaliraj(double skalar)
{
	if(skalar<=0)	throw std::domain_error("Neispravan faktor skaliranja");
	else r*=skalar;
}
void Krug::Ispisi() const
{
	std::cout<< std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnik()<<" O="<<DajObim()<<" P="<<DajPovrsinu();
}
class Valjak
{
	Krug baza;
	double visina;
public:
	Valjak(double r, double h);
	void Postavi(double r, double h);
	double DajPoluprecnikBaze() const
	{
		return baza.DajPoluprecnik();
	}
	double DajVisinu() const
	{
		return visina;
	}
	double DajPovrsinu() const
	{
		return 2*baza.DajPovrsinu()+DajVisinu()*baza.DajObim();
	}
	double DajZapreminu() const
	{
		return baza.DajPovrsinu()*DajVisinu();
	}
	Krug DajBazu()	const
	{
		return baza;
	}
	void Skaliraj(double skalar);
	void Ispisi() const;
};
Valjak::Valjak(double r, double h):baza(r)
{
	if(h<=0) throw std::domain_error("Neispravna visina");
	baza.Postavi(r);
	visina=h;
}
void Valjak::Postavi(double r, double h)
{
	baza.Postavi(r);
	if(h<=0) throw std::domain_error("Neispravna visina");
	visina=h;
}
void Valjak::Skaliraj(double skalar)
{
	if(skalar<=0) throw std::domain_error("Neispravan faktor skaliranja");
	visina*=skalar;
	baza.Skaliraj(skalar);
}
void Valjak::Ispisi() const
{
	std::cout<< std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnikBaze()<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();
}
int main ()
{
	try{
		Valjak valjak=Valjak(2.5, 3);
		Krug krug=valjak.DajBazu();
		krug.Ispisi();
		valjak.Ispisi();
	}
	catch (std::domain_error dp){
		std::cout<<dp.what();
	}
	return 0;
}
