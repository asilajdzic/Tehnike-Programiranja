#include <iostream>
#include <string>
#include <vector>
#include <cctype>
std::vector<int> BrojUStringu (std::string s)
{
    std::vector<int> v;
    for(int i=0; i<s.length(); i++) {
        int broj=0;
        bool JeLiBroj=false;
        while(i<s.length() && isalnum(s.at(i))) {
            if(isdigit(s.at(i))) {
                JeLiBroj=true;
                broj*=10;
                broj+=s.at(i)-'0';
            } else {
                JeLiBroj=false;
                break;
            }
            i++;
        }
        if(JeLiBroj)
            v.push_back(broj);
    }
    return v;
} // ne moze ovako :D
std::vector<int> BrojeviUStringu (std::string s)
{
    std::vector<int> v;
    for(int i=0; i<s.length(); i++) {
        std::string rijec;
        while(i<s.length() && isalnum(s.at(i))) {
            rijec.push_back(s.at(i));
            i++;
        }
        if(rijec.length()) {
            bool treba=true;
            for(int k=0; k<rijec.length(); k++)
                if(!isdigit(rijec.at(k)))   treba=false;
            if(treba) {
                int broj=0;
                for(int k=0; k<rijec.length(); k++) {
                    broj*=10;
                    broj+=rijec.at(k)-'0';
                }
                v.push_back(broj);
            }
        }
    }
    return v;
} //ruzno je ali radi
int main()
{
    std::string s1="2PAC i U2 imaju koncert";
    std::string s2="120 hrabrih studenata izašlo na ispit 35 ih je odustalo, ostalo ih 85..";
    auto v1=BrojeviUStringu(s1);
    auto v2=BrojeviUStringu(s2);
    std::cout<<"\nPrvi vektor:\n";
    for(int i=0; i<v1.size(); i++)
        std::cout<<v1.at(i)<<" ";
    std::cout<<"\nDrugi vektor:\n";
    for(int i=0; i<v2.size(); i++)
        std::cout<<v2.at(i)<<" ";
    return 0;
}
