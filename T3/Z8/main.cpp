//TP 2018/2019: Tutorijal 3, Zadatak 8
#include <iostream>
#include <string>
#include <stdexcept>
using std::cin;
using std::cout;
std::string IzdvojiRijec(std::string s, int n)
{
    if(n<=0) throw std::range_error("IZUZETAK: Pogresan redni broj rijeci! ");
    int brojac_rijeci=0;
    std::string izlaz;
    bool razmak=true;
    for(int i=0; i<s.length(); i++) {
        if(s[i]==' ')
            razmak=true;
        else if(razmak) {
            razmak=false;
            brojac_rijeci++;
        }
        if(brojac_rijeci==n) {
            while(s[i]!=' ' && i<s.length()) {
                izlaz.push_back(s[i]);
                i++;
            }
            return izlaz;
        }
    }
    if(n>brojac_rijeci)
        throw std::range_error("IZUZETAK: Pogresan redni broj rijeci! ");
    return izlaz;
}

int main ()
{
    try {
        cout<<"Unesite redni broj rijeci: ";
        int n;
        cin>>n;
        std::string recenica;
        cout<<"Unesite recenicu: ";
        std::cin>>std::ws;
        std::getline(cin,recenica);
        auto rijec=IzdvojiRijec(recenica,n);
        cout<<"Rijec na poziciji "<<n<<" je "<<rijec;
    } catch(std::range_error izuzetak) {
        std::cout << izuzetak.what() << std::endl;
    }
    return 0;
}
