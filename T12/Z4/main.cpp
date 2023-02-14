#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
class Kompleksni
{
	double re, im;
public:
	Kompleksni(double re = 0, double im = 0) : re(re), im(im) {}
	friend Kompleksni operator +(const Kompleksni &a)
	{
		return a;
	}
	friend Kompleksni operator -(const Kompleksni &a)
	{
		return {-a.re, -a.im};
	}
	friend Kompleksni operator +(const Kompleksni &a, const Kompleksni &b)
	{
		return {a.re + b.re, a.im + b.im};
	}
	friend Kompleksni operator -(const Kompleksni &a, const Kompleksni &b)
	{
		return {a.re - b.re, a.im - b.im};
	}
	friend Kompleksni operator *(const Kompleksni &a, const Kompleksni &b)
	{
		return {a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
	}
	friend Kompleksni operator /(const Kompleksni &a, const Kompleksni &b)
	{
		double pomocna = b.re * b.re + b.im * b.im;
		return {(a.re * b.re + a.im * b.im) / pomocna, (a.im * b.re - a.re * b.im) / pomocna};
	}
	friend bool operator ==(const Kompleksni &a, const Kompleksni &b)
	{
		return a.re == b.re && a.im == b.im;
	}
	friend bool operator !=(const Kompleksni &a, const Kompleksni &b)
	{
		return !(a == b);
	}
	friend Kompleksni &operator +=(Kompleksni &a, const Kompleksni &b)
	{
		a.re += b.re;
		a.im += b.im;
		return a;
	}
	friend Kompleksni &operator -=(Kompleksni &a, const Kompleksni &b)
	{
		a.re -= b.re;
		a.im -= b.im;
		return a;
	}
	friend Kompleksni &operator *=(Kompleksni &a, const Kompleksni &b)
	{
		double pomocna = a.re * b.im + a.im * b.re;
		a.re = a.re * b.re - a.im * b.im;
		a.im = pomocna;
		return a;
	}
	friend Kompleksni &operator /=(Kompleksni &a, const Kompleksni &b)
	{
		double pom1 = a.im * b.re - a.re * b.im, pom2 = b.re * b.re + b.im * b.im;
		a.re = (a.re * b.re + a.im * b.im) / pom2;
		a.im = pom1 / pom2;
		return a;
	}
	friend std::ostream &operator <<(std::ostream &tok, const Kompleksni &a)
	{
		if(a.re!=0 || a.im==0)
			tok<<a.re;
		if(a.im!=0) {
			if(a.im>0) {
				if(a.re!=0)
					tok<<"+";
				if(a.im!=1)
					tok<<a.im;
				tok<<"i";
			}
			if(a.im<0)	{
				if(a.im!=-1)
					tok<<a.im<<"i";
				else tok<<"-i";
			}
		}
		return tok;
	}
	friend std::istream &operator >>(std::istream &tok, Kompleksni &a);
	friend double real(const Kompleksni &a)
	{
		return a.re;
	}
	friend double imag(const Kompleksni &a)
	{
		return a.im;
	}
	friend double abs(const Kompleksni &a)
	{
		return std::sqrt(a.re * a.re + a.im * a.im);
	}
	friend double arg(const Kompleksni &a)
	{
		return std::atan2(a.im, a.re);
	}
	friend Kompleksni conj(const Kompleksni &a)
	{
		return {a.re, -a.im};
	}
	friend Kompleksni sqrt(const Kompleksni &a)
	{
		double rho = std::sqrt(abs(a)), phi = arg(a) / 2;
		return {rho * std::cos(phi), rho * std::sin(phi)};
	}
};
std::istream &operator >>(std::istream &tok, Kompleksni &a)
{
	char znak='\0';
	int predznak=1;
	tok>>std::ws;
	if(!isdigit(tok.peek()) && tok.peek()!='-' && tok.peek()!='i') tok.setstate(std::ios::failbit);
	if(tok.peek()=='i') {
		a.re=0;
		a.im=1;
		return tok;
	}
	if(tok.peek()=='-') {
		predznak=-1;
		tok.get(znak);
	}
	if(tok.peek()=='i') {
		a.re=0;
		a.im=predznak;
		return tok;
	}
	tok>>a.re;
	a.re*=predznak;
	tok>>znak;
	if(znak=='\n') {
		a.im=0;
		return tok;
	}
	if(znak=='i') {
		a.im=a.re;
		a.re=0;
	}
	predznak=1;
	if(znak=='-')
		predznak=-1;
	else if(znak!='+')	tok.setstate(std::ios::failbit);
	if(tok.peek()=='i') {
		a.im=predznak;
	} else {
		tok>>a.im>>znak;
		a.im*=predznak;
	}
	if(znak!='i')
		tok.setstate(std::ios::failbit);
	return tok;
}
// {
// 	std::string s;
// 	tok>>s;
// 	if(s.length()==1 && s.at(0)=='0') {
// 		a.re=0;
// 		a.im=0;
// 		return tok;
// 	}
// 	int predznak=1;
// 	if(!s.length()) tok.setstate(std::ios::failbit);
// 	for(int i=0; i<s.length(); i++) {
// 		int broj=0;
// 		while(i<s.length() && s.at(i)>='0' && s.at(i)<='9') {
// 			broj*=10;
// 			broj+=s.at(i)-'0';
// 			i++;
// 		}
// 		if(i>=s.length()) {
// 			a.im=0;
// 			a.re=broj;
// 			return tok;
// 		} //za slucaj da je unesen samo realni dio
// 		else if(i<s.length() && s.at(i)=='i') {
// 			if(broj!=0)
// 				a.im=broj*predznak;
// 			else a.im=predznak;} // ako je na indeksu i slovo i postavljamo imag na broj ili 1/-1
// 		else if(broj) {
// 			a.re=broj*predznak;
// 			predznak=1;
// 		}
// 		 if(s.at(i)=='-')
// 			predznak=-1;
// 	}
// 	return tok;
// }
int main()
{
	Kompleksni z;
	std::cin>>z;
	std::cout <<z;
	//<< Kompleksni(0) << " " << Kompleksni(1) << " " << Kompleksni(5) << " "
	//<< Kompleksni(-1) << " " << Kompleksni(-5) << " " << Kompleksni(0, 1) << " "
	//<< Kompleksni(0, -1) << " " << Kompleksni(0, 5) << " " << Kompleksni(0, -5) << std::endl;
	return 0;
}
