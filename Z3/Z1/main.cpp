//TP 2018/2019: Zadaća 3, Zadatak 1
#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>
#include <cmath>
void MinMax(std::vector<std::pair<double,double>> v, double &min, double &max)
{
    min=v.at(0).first;
    max=v.at(0).first;
    for(int i=1; i<v.size(); i++) {
        if(min>v.at(i).first) min=v.at(i).first;
        if(max<v.at(i).first) max=v.at(i).first;
    }
}
double f(double x)
{
    return x*x+sin(x)+log(x+1);
}
std::function<double(double)> LagrangeovaInterpolacija(std::vector<std::pair<double,double>> v)
{
    for(int i=0; i<v.size(); i++) {
        for(int j=i+1; j<v.size(); j++)
            if(v.at(i).first==v.at(j).first)    throw std::domain_error("Neispravni cvorovi");
    } // izuzetak ako su iste x koordinate
    int duzina=v.size();
    return[v,duzina](double x) {
        for(int i=0; i<duzina; i++)
            if(x==v.at(i).first)    return v.at(i).second;
        double suma=0;
        for(int i=0; i<duzina; i++) {
            double f=v.at(i).second;
            for(int j=0; j<duzina; j++)
                if(i!=j)
                    f*=(x-v.at(j).first)/(v.at(i).first-v.at(j).first);
            suma+=f;
        }
        return suma;
    };
}
std::function<double(double)>LagrangeovaInterpolacija(std::function<double(double)>f,double x_min,double x_max, double dx)
{
    if(dx<=0 || x_min>x_max)    throw std::domain_error("Nekorektni parametri");
    std::vector<std::pair<double, double>> v;
    for(; x_min<=x_max; x_min+=dx)
        v.push_back(std::make_pair(x_min,f(x_min)));
    return LagrangeovaInterpolacija(v);
}
int main ()
{
    try {
        for(;;) {
            int opcija;
            std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
            std::cin>>opcija;
            if(opcija!=1 && opcija!=2) {
                std::cout<<"Nepoznat slucaj!";
                return 0;
            }
            if(opcija==1) {
                std::cout<<"Unesite broj cvorova: ";
                int brojCvorova;
                std::cin>>brojCvorova;
                if(brojCvorova<1) {
                    std::cout<<"Broj cvorova mora biti pozitivan broj!";
                    return 0;
                }
                std::vector<std::pair<double, double>> v(brojCvorova);
                std::cout<<"Unesite cvorove kao parove x y: ";
                for(int i=0; i<brojCvorova; i++)
                    std::cin>>v.at(i).first>>v.at(i).second;
                LagrangeovaInterpolacija(v)(1); //zbog izuzetka
                for(;;) {
                    std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                    double argument;
                    std::cin>>argument;
                    if(!std::cin) return 0;
                    double min,max;
                    MinMax(v,min,max);
                    bool ekstrapolacija=argument<min || argument>max;
                    if(ekstrapolacija)
                        std::cout<<"f("<<argument<<") = "<<LagrangeovaInterpolacija(v)(argument)<<" [ekstrapolacija]"<<std::endl;
                    else
                        std::cout<<"f("<<argument<<") = "<<LagrangeovaInterpolacija(v)(argument)<<std::endl;
                }
            } //radi
            else if(opcija==2) {
                std::cout<<"Unesite krajeve intervala i korak: ";
                double x_min,x_max,dx;
                std::cin>>x_min>>x_max>>dx;
                LagrangeovaInterpolacija(f,x_min,x_max,dx)(1);//zbog izuzetka
                std::vector<std::pair<double, double>> v;
                for(double i=x_min; i<=x_max; i+=dx)
                    v.push_back(std::make_pair(i,f(i)));
                for(;;) {
                    double argument=0;
                    std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                    std::cin>>argument;
                    if(!std::cin) return 0;
                    std::cout<<"f("<<argument<<") = "<<f(argument)<<" ";
                    std::cout<<"P("<<argument<<") = "<<LagrangeovaInterpolacija(f,x_min,x_max,dx)(argument);
                    if(argument>x_max || argument<x_min)
                        std::cout<<" [ekstrapolacija]";
                    std::cout<<std::endl;
                }
            }
        }
    } catch(std::domain_error dp) {
        std::cout<<"IZUZETAK: "<<dp.what()<<"!";
    }
}
