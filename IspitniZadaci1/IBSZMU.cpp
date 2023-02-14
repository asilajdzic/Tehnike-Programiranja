#include <iostream>
#include <vector>

enum class Kriterij {Veca, Manja, Jednaka};

std::vector<int> IzbaciPonavljajuce (std::vector<int> vektor)
{
    for(int i=0; i<vektor.size(); i++) {
        for(int j=i+1; j<vektor.size(); j++) {
            if(vektor.at(i)==vektor.at(j)) {
                vektor.erase(vektor.begin()+j);
                j--;
            }
        }
    }
    return vektor;
}

int MultiplikativnaOtpornost (int n)
{
    if (n<0) n=-1*n;
    int cifra;
    int brojac=0;
    while(n>9) {
        int proizvod=1;
        do {
            cifra=n%10;
            proizvod*=cifra;
            n/=10;
        } while(n>0);
        n=proizvod;
        brojac++;
    }
    return brojac;
}

std::vector<int> IBSZMU (std::vector<int> vektor, int n, Kriterij kriterij)
{
    std::vector<int> v=IzbaciPonavljajuce(vektor);
    for(int i=0; i<v.size(); i++) std::cout<<v.at(i)<<" ";
    std::cout<<"\n";
    std::vector<int> novi;
    if(kriterij==Kriterij::Veca) {
        std::cout<<"Provjeravam VECE: \n";
        for(int i=0; i<v.size(); i++) {
            if(MultiplikativnaOtpornost(v.at(i))>n) {
                novi.push_back(v.at(i));
            }
        }
    }

    else if(kriterij==Kriterij::Manja) {
        std::cout<<"Provjeravam MANJE: \n";
        for(int i=0; i<v.size(); i++) {
            if(MultiplikativnaOtpornost(v.at(i))<n) {
                novi.push_back(v.at(i));
            }
        }
    }


    else if(kriterij==Kriterij::Jednaka) {
        std::cout<<"Provjeravam JEDNAKE: \n";
        for(int i=0; i<v.size(); i++) {
            if(MultiplikativnaOtpornost(v.at(i))==n) {
                novi.push_back(v.at(i));
            }
        }
    }
    return novi;
}
int main ()
{
    std::vector<int> v, v_manja, v_veca, v_jednaka;
    int n;
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    for(int i=0; ; i++) {
        std::cin>>n;
        if(n==0) break;
        v.push_back(n);
    }

    int prag;
    std::cout<<"Unesite zeljeni prag za multiplikativnu otpornost: ";
    std::cin>> prag;

    std::cout<<"\nBrojevi cija je multiplikativna otpornost manja od zadane: ";
    v_manja= IBSZMU(v, prag, Kriterij::Manja);
    if(v_manja.size()==0) std::cout<<"Nema takvih brojeva";
    else {
        for(int i=0; i< v_manja.size(); i++) {
            std::cout<< v_manja.at(i)<< " ";
        }
    }
    std::cout<<"\nBrojevi cija je multiplikativna otpornost veca od zadane: ";
    v_veca= IBSZMU(v,prag, Kriterij::Veca);
    if(v_veca.size() == 0) std::cout<<"Nema takvih brojeva";
    else {
        for(int i=0; i<v_veca.size(); i++) {
            std::cout<< v_veca.at(i)<< " ";
        }
    }
    std::cout<<"\nBrojevi cija je multiplikativna otpornost jednaka zadanoj: ";
    v_jednaka=IBSZMU(v,prag, Kriterij::Jednaka);
    if(v_jednaka.size()==0) std::cout<<"Nema takvih brojeva";
    else {
        for(int i=0; i<v_jednaka.size(); i++) {
            std::cout<<v_jednaka.at(i)<<" ";
        }
    }
    return 0;
}
