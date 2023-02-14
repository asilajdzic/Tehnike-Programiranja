//TP 2016/2017: Zadaća 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <deque>
#include <vector>
#include <utility>
using std::cin;
using std::cout;
typedef std::deque<std::vector<double>> dekVektora;
enum class Smjer {Opadajuci,Rastuci};
bool JeLiPodniz (dekVektora d, std::vector<double> v)
{
    for(int i=0; i<d.size(); i++) {
        int m=0,n=0;
        while(m<d.at(i).size() && n<v.size()) {
            if(d.at(i).at(m)==v.at(n)) {
                m++;
                n++;
                if(n==v.size())
                    return true;
            } else {
                m=m-n+1;
                n=0;
            }
        }
    }
    return false;
} // dobra 
bool JeLiBalansiran (std::vector<double> v)
{
    double suma1=0;
    double suma2=0;
    for(int i=0; i<v.size(); i++) {
        if((v.size()%2==0 && i<v.size()/2) || (v.size()%2==1 && i<=v.size()/2))
            suma1+=v.at(i);
        if(i>=v.size()/2)
            suma2+=v.at(i);
    }
    return suma1==suma2;
} //provjeriti
dekVektora MaksimalniBalansiraniPodniz (std::vector<double> v)
{
    dekVektora izlaz;
    for(int i=0; i<v.size(); i++) {
        std::vector<double> pomocni;
        for(int j=i; j<v.size(); j++) {
            pomocni.push_back(v.at(j));
        } //dodjela od itog clana do kraja pomocnom vektoru
        for(; pomocni.size()>1; pomocni.resize(pomocni.size()-1))
            if(JeLiBalansiran(pomocni) && !JeLiPodniz(izlaz,pomocni))
                izlaz.push_back(pomocni);
        //smanjivanje duzine vektora
    }
    return izlaz;
} // popraviti ovdje nesta
dekVektora Transformacija(dekVektora d,Smjer kakav)
{
    for(int i=0; i<d.size(); i++)
        if(!JeLiBalansiran(d.at(i)))
            throw std::domain_error("Dek vektora je neispravan.");
    for(int i=0; i<d.size(); i++) {
        if(kakav==Smjer::Rastuci) {
            int j=0;
            for(; j<d.at(i).size()/2; j++) {
                int mini=j;
                for(int k=j+1; k<d.at(i).size()/2; k++)
                    if(d.at(i).at(mini)>d.at(i).at(k))
                        mini=k;
                std::swap(d.at(i).at(mini),d.at(i).at(j));
            }
            if(d.at(i).size()%2)
                j++;
            for(; j<d.at(i).size(); j++) {
                int maxi=j;
                for(int k=j+1; k<d.at(i).size(); k++)
                    if(d.at(i).at(maxi)<d.at(i).at(k))
                        maxi=k;
                std::swap(d.at(i).at(maxi),d.at(i).at(j));
            }
        }
        if(kakav==Smjer::Opadajuci) {
            int j=0;
            for(; j<d.at(i).size()/2; j++) {
                int maxi=j;
                for(int k=j+1; k<d.at(i).size()/2; k++)
                    if(d.at(i).at(maxi)<d.at(i).at(k))
                        maxi=k;
                std::swap(d.at(i).at(maxi),d.at(i).at(j));
            }
            if(d.at(i).size()%2)
                j++;
            for(; j<d.at(i).size(); j++) {
                int mini=j;
                for(int k=j+1; k<d.at(i).size(); k++)
                    if(d.at(i).at(mini)>d.at(i).at(k))
                        mini=k;
                std::swap(d.at(i).at(mini),d.at(i).at(j));
            }
        }
    }
    return d;
} //dobra
int main ()
{
    cout<<"Unesite broj elemenata niza: ";
    int n;
    cin>>n;
    cout<<"Unesite elemente niza: ";
    std::vector<double> v(n);
    for(int i=0; i<n; i++)
        cin>>v.at(i);
    Smjer kakav;
    int unos;
    cout<<"Unesite tip: (1 - rastuci, 0 - opadajuci): ";
    cin>>unos;
    kakav=Smjer(unos);
    cout<<"\nMaksimalni balansirani podnizovi: \n";
    auto balansirani=MaksimalniBalansiraniPodniz(v);
    for(int i=0; i<balansirani.size(); i++) {
        for(int j=0; j<balansirani.at(i).size(); j++)
            cout<<balansirani.at(i).at(j)<<" ";
        cout<<"\n";
    }
    auto transformisani=Transformacija(balansirani,kakav);
    cout<<"Savrseni balansirani podnizovi nakon transformacije: \n";
    for(int i=0; i<transformisani.size(); i++) {
        for(int j=0; j<transformisani.at(i).size(); j++)
            cout<<transformisani.at(i).at(j)<<" ";
        cout<<"\n";
    }
    return 0;
}
