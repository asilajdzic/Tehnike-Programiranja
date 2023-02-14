#include <iostream>
#include <algorithm>
#include <string>
template <class input1, class input2>
input1 NadjiPodblok(input1 poc1, input1 kraj1, input2 poc2, input2 kraj2)
{
    while(poc1!=kraj1) {
        if(*poc1==*poc2) {
            auto poc11=poc1;
            auto poc22=poc2;
            while(poc11!=kraj1 && poc22!=kraj2 && *poc11++==*poc22++) {
            }
            if(poc22==kraj2)  return poc1;
        }
        poc1++;
    }
    return kraj1;
}
int main()
{
    std::string string("Adin bi sta i polozio");
    std::string podstring("polozio");
    auto p=NadjiPodblok(string.begin(),string.end(),podstring.begin(),podstring.end());
    if(p==string.end()) std::cout<<"Nema tog bloka";
    else std::for_each(p,p+podstring.length(),[](char c) {
        std::cout<<c;
    });
    return 0;
    //radi samo sto je ruzno do bola
}
