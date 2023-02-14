//TP 2016/2017: Zadaća 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
std::vector<int> IzdvojiSimetricneTernarne   (std::vector<int> v, bool simetricni=true)
{
    std::vector<int> izlaz;
    for(int i=0; i<v.size(); i++) {
        std::vector<int> broj;
        int tmp=v.at(i);
        while(tmp!=0) {
            broj.push_back(tmp%10);
            tmp/=10;
        }
        std::vector<int> ternarni;
        tmp=v.at(i);
        while(tmp!=0) {
            ternarni.push_back(tmp%3);
            tmp/=3;
        }
        bool jesuLiSimetricni;
        bool jesuLiSimetricniT;
        std::vector<int> ternarni2=ternarni;
        std::vector<int> broj2=broj;
        std::reverse(std::begin(broj),std::end(broj));
        std::reverse(std::begin(ternarni),std::end(ternarni));
        jesuLiSimetricniT=ternarni==ternarni2;
        jesuLiSimetricni=broj==broj2;
        if(jesuLiSimetricniT) {
            if(simetricni == jesuLiSimetricni) {
                bool postoji=false;
                for(int j=0; j<izlaz.size(); j++)
                    if(izlaz.at(j)==v.at(i))
                        postoji=true;
                if(!postoji)
                    izlaz.push_back(v.at(i));
            }
        }
    }
    return izlaz;
}
int main ()
{
    cout<<"Unesite broj elemenata niza: ";
    int n;
    bool simetricni;
    cin>>n;
    cout<<"Unesite elemente niza: ";
    std::vector<int> v(n);
    for(int i=0; i<n; i++)
        cin>>v.at(i);
    cout<<"Unesite parametar (1 ili 0): ";
    cin>>simetricni;
    auto izdvojeni=IzdvojiSimetricneTernarne(v,simetricni);
    cout<<"Izdvojeni elementi su: ";
    for(int i=0; i<izdvojeni.size(); i++) {
        if(i<izdvojeni.size()-1)
            cout<<izdvojeni.at(i)<<", ";
        else
            cout<<izdvojeni.at(i);
    }
    return 0;
}
