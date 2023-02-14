//TP 2016/2017: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
using std::cin;
using std::cout;
std::string IstakniSavrsenoRitmicneRijeci(std::string s)
{
   std::string izlaz;
   for(int i=0; i<s.length(); i++) {
      int j;
      bool ritmicna=true;
      bool samoglasnik=true,suglasnik=true;
      for(j=i; j<s.length(); j++) {
         if(s.at(j)>='a' && s.at(j)<='z' || s.at(j)>='A' && s.at(j)<='Z') {
            if(samoglasnik && !(s.at(j)=='a' || s.at(j)=='e' || s.at(j)=='i' || s.at(j)=='o' || s.at(j)=='u' || s.at(j)=='A' || s.at(j)=='E' || s.at(j)=='I' || s.at(j)=='O' || s.at(j)=='U')) {
               samoglasnik=false;
               suglasnik=true;
            } else if(suglasnik && (s.at(j)=='a' || s.at(j)=='e' || s.at(j)=='i' || s.at(j)=='o' || s.at(j)=='u' || s.at(j)=='A' || s.at(j)=='E' || s.at(j)=='I' || s.at(j)=='O' || s.at(j)=='U')) {
               samoglasnik=true;
               suglasnik=false;
            } else ritmicna=false;
         } else
            break;
      }
      if(ritmicna && s.at(i)!=' ' && j-i>1) {
         izlaz.push_back('(');
         for(; i<j; i++)
            izlaz.push_back(s.at(i));
         izlaz.push_back(')');
         if(j<s.length())
            izlaz.push_back(' ');
      } else {
         for(; i<j; i++)
            izlaz.push_back(s.at(i));
         izlaz.push_back(' ');
      }
   }
   return izlaz;
}
int main ()
{
   cout<<"Unesite recenicu (ENTER za kraj): ";
   std::string s;
   std::getline(cin,s);
   cout<<"Recenica sa istaknutim savrseno ritmicnim rijecima glasi:\n";
   cout<<IstakniSavrsenoRitmicneRijeci(s);
   return 0;
}
2