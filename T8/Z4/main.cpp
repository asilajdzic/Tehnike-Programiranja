//TP 2018/2019: Tutorijal 8, Zadatak 4
#include <iostream>
#include <string>
#include <map>
std::string ZamijeniPremaRjecniku (std::string s, std::map<std::string, std::string> m)
{
    for(int i=0; i<s.length(); i++) {
        if(s.at(i)>='a' || s.at(i)<='z') {
            int j;
            for(j=i; j<s.length(); j++)
                if(s.at(j)<'a' || s.at(j)>'z') break;
            std::string tmp=s.substr(i,j-i);
            auto it=m.find(tmp);
            if(it!=m.end()) {
                s.erase(i,j-i);
                s.insert(i,it->second);
                i+=it->second.length()-1;
            } else i=j;
        }
    }
    return s;
}
int main ()
{
    return 0;
}
