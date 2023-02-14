//TP 2016/2017: Zadaća 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iomanip>
using std::cin;
using std::cout;
typedef std::vector<std::vector<double>> matrica;
typedef std::vector<std::vector<std::vector<double>>> vektorMatrica;
matrica MnozenjeMatrica (matrica m1,matrica m2)
{
   int red1=0,kol1=0,red2=0,kol2=0;
   red1=m1.size();
   if(red1)
      kol1=m1.at(0).size();
   red2=m2.size();
   if(red2)
      kol2=m2.at(0).size();
   if(kol1!=red2)
      throw std::domain_error ("Nije moguce mnozenje matrica!");
   for(int i=0; i<red1; i++) {
      if(kol1!=m1.at(i).size())
         throw std::domain_error ("Neispravna matrica!");
   }
   for(int i=0; i<red2; i++) {
      if(kol2!=m2.at(i).size())
         throw std::domain_error ("Neispravna matrica!");
   }
   matrica proizvod(kol1);
   for(int i=0; i<red1; i++) {
      for(int j=0; j<kol2; j++) {
         double element=0;
         for(int k=0; k<kol1; k++) {
            element+=m1.at(i).at(k)*m2.at(k).at(j);
         }
         proizvod.at(i).push_back(element);
      }
   }
   return proizvod;
} // dobra
vektorMatrica DoolitleLU (matrica h)
{
   vektorMatrica lu;
   if(!h.size())
      return lu;
   if(h.size()!=h.at(0).size())
      throw std::domain_error ("Matrica mora biti kvadratnog oblika!");
   for(int i=0; i<h.size()-1; i++)
      if(h.at(i).size()!=h.at(i+1).size())
         throw std::domain_error ("Neispravna matrica!");
   int n=h.size();
   matrica l(n,std::vector<double>(n));
   matrica u(n,std::vector<double>(n));
   for(int i=0; i<n; i++)
      l.at(i).at(i)=1;
   for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
         if(j<i) {
            l.at(i).at(j)=h.at(i).at(j)/u.at(j).at(j);
            for(int k=0; k<j; k++) {
               l.at(i).at(j)-=(l.at(i).at(k)*u.at(k).at(j))/u.at(j).at(j);
            }
         }
         if(j>=i) {
            u.at(i).at(j)=h.at(i).at(j);
            for(int m=0; m<i; m++)
               u.at(i).at(j)-=l.at(i).at(m)*u.at(m).at(j);
         }
      }
   }
   lu.push_back(l);
   lu.push_back(u);
   return lu;
} // dobra
bool ProvjeriFaktorizaciju(matrica h,vektorMatrica lu) // dobra
{
   try {
      return (DoolitleLU(h)==lu);
   }
   catch (std::domain_error e){
      return false;
   }
}
int main ()
{
   try {
      cout<<"Unesite dimenziju kvadratne matrice H: ";
      int n;
      cin>>n;
      matrica h(n,std::vector<double>(n));
      cout<<"Unesite elemente matrice H:\n";
      for(int i=0; i<n; i++) {
         cout<<"Elementi "<<i+1<<". reda: ";
         for(int j=0; j<n; j++)
            cin>>h.at(i).at(j);
      }
      auto lu=DoolitleLU(h);
      cout<<"Matrica L: ";
      for(int i=0; i<n; i++) {
         cout<<"\n";
         for(int j=0; j<n; j++)
            std::cout<<std::setw(9)<<std::setprecision(4)<<std::fixed<<lu.at(0).at(i).at(j);
      }
      cout<<"\nMatrica U: ";
      for(int i=0; i<n; i++) {
         cout<<"\n";
         for(int j=0; j<n; j++)
            std::cout<<std::setw(9)<<std::setprecision(4)<<std::fixed<<lu.at(1).at(i).at(j);
      }
     /* cout<<"\n"<<ProvjeriFaktorizaciju(h,lu)<<"\n";
      auto proizvod=MnozenjeMatrica(lu.at(0),lu.at(1));
      cout<<"\n Proizvod LU glasi: \n";
      for(int i=0; i<n; i++) {
         cout<<"\n";
         for(int j=0; j<n; j++)
            std::cout<<std::setw(9)<<std::setprecision(4)<<std::fixed<<proizvod.at(i).at(j);
      }*/ //provjera
   }
   catch(std::domain_error e) {
   cout<<e.what();
   }
   return 0;
}