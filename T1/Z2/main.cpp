//TP 2018/2019: Tutorijal 1, Zadatak 2
#include <iostream>
#include <cmath>
int main ()
{
    double a,b,c;
    std::cout<<"Unesite tri broja: ";
    std::cin>>a>>b>>c;
    if(a+b<=c || a+c<=b || b+c<=a || a<=0 || b<=0 || c<=0)
    std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
    else {
        double povrsina=0,s;
        s=(a+b+c)/2;
        povrsina=sqrt(s*(s-a)*(s-b)*(s-c));
        std::cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<a+b+c<<"."<<std::endl;
        std::cout<<"Njegova povrsina iznosi "<<povrsina<<"."<<std::endl;
        double alfa,beta,gama;
        gama=acos((a*a+b*b-c*c)/(2*a*b));
        beta=acos((a*a+c*c-b*b)/(2*a*c));
        alfa=acos((b*b+c*c-a*a)/(2*b*c));
        int ugao;
        ugao=gama*180/(4*atan(1))*3600;
        if(alfa<gama)
        ugao=alfa*180/(4*atan(1))*3600;
        if(beta<alfa && beta<gama)
        ugao=beta*180/(4*atan(1))*3600;
        std::cout<<"Njegov najmanji ugao ima "<<ugao/3600<<" stepeni, "<<ugao%3600/60<<" minuta i "<<ugao%60<<" sekundi.";
    }
	return 0;
}