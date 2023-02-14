#include<iostream>
#include<string>
#include<deque>
#include<algorithm>
int main ()
{
    std::cout<<"Unesite 5 stringova: ";
    std::deque<std::string> d(5);
    for(int i=0; i<5; i++) {
        std::getline(std::cin, d.at(i));
    }
    int brojac=0;
    int broj_samoglasnika;
    std::cout<<"Unesite dozvoljeni broj samoglasnika: ";
    std::cin>>broj_samoglasnika;
    std::copy_if(d.begin(),d.end(),d.begin(),[&brojac,broj_samoglasnika](std::string s) {
        int br=0;
        for(int i=0; i<s.length(); i++)
            if(s.at(i)=='A' || s.at(i)=='E' || s.at(i)=='I' || s.at(i)=='O' || s.at(i)=='U' || s.at(i)=='a'
                    || s.at(i)=='e' || s.at(i)=='i' || s.at(i)=='o' || s.at(i)=='u')
                br++;
        if(br>broj_samoglasnika) return false;
        brojac++;
        return true;
    });
    for(int i=0; i<brojac; i++)
        std::cout<<d.at(i)<<"\n";
    return 0;
}
