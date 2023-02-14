#include <iostream>
#include <vector>

enum class Kriterij {Veca, Manja, Jednaka};

std::vector<int> IBSZMU(std::vector<int> Ulazni_Vektor, int k, Kriterij koji_je)
{
    for(int i=0; i<Ulazni_Vektor.size(); i++)
        for(int j=i+1; j<Ulazni_Vektor.size(); j++)
            if(Ulazni_Vektor.at(i)==Ulazni_Vektor.at(j)) {
                Ulazni_Vektor.erase(Ulazni_Vektor.begin()+j);
                j--;
            }
    std::vector<int> Izlazni_Vektor;
    for(int i=0; i<Ulazni_Vektor.size(); i++) {
        int element=Ulazni_Vektor.at(i);
        std::cout<<"Broj: "<<element<<" ";
        int brojac=0;
        int proizvod=1;
        if(element<0) element*=-1;
        while(element!=0) {
            proizvod*=element%10;
            element/=10;
            if(element<10 && element!=0) {
                proizvod*=element%10;
                if(proizvod>9) {
                    element=proizvod;
                    std::cout<<"\nproizvod: "<<proizvod<<std::endl;
                }
                brojac++;
                proizvod=1;
            }
        }
        std::cout<<"MO: "<<brojac<<std::endl;
        if(koji_je==Kriterij::Manja && brojac<k) Izlazni_Vektor.push_back(Ulazni_Vektor.at(i));
        else if(koji_je==Kriterij::Veca && brojac>k) Izlazni_Vektor.push_back(Ulazni_Vektor.at(i));
        else if(koji_je==Kriterij::Jednaka && brojac==k) Izlazni_Vektor.push_back(Ulazni_Vektor.at(i));
    }
    return Izlazni_Vektor;
}

int main ()
{
    std::vector<int> Ulazni_Vektor;
    std::cout<<"Unesite elemente vektora: ";
    int element;
    for(;;) {
        std::cin>>element;
        if(element==0) break;
        Ulazni_Vektor.push_back(element);
    }
    int k;
    std::cout << "Unesite multiplikativnu otpornost: ";
    while(!(std::cin >> k), (k<=0)) {
        std::cout << "Unesite multiplikativnu otpornost: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    std::vector<int> Manja_Otp;
    Manja_Otp= IBSZMU(Ulazni_Vektor,k,Kriterij::Manja);
    std::vector<int> Veca_Otp;
    Veca_Otp= IBSZMU(Ulazni_Vektor,k,Kriterij::Veca);
    std::vector<int> Jednaka_Otp;
    Jednaka_Otp= IBSZMU(Ulazni_Vektor,k,Kriterij::Jednaka);
    std::cout<<"Manja: ";
    for (int j : Manja_Otp)
        std::cout << j << " ";
    std::cout << std::endl;
    std::cout<<"Veca: ";
    for (int j : Veca_Otp)
        std::cout << j << " ";
    std::cout << std::endl;
    std::cout<<"Jednaka: ";
    for (int j : Jednaka_Otp)
        std::cout << j << " ";
    std::cout << std::endl;

    return 0;
}
