#include <iostream>
#include <string>
#include <algorithm>
int main()
{
    int n;
    std::cout<<"Unesi n: ";
    std::cin>>n; //vjv bi trebalo ici sa cin.ignore i getline
    std::string *niz=new std::string[n];
    for(int i=0; i<n; i++)
        std::cin>>niz[i];
    std::sort(niz,niz+n,[](std::string s1, std::string s2) {
        return s1<s2;
    });
    for(int i=0;i<n;i++)
        std::cout<<"\n"<<niz[i];
    delete[] niz;
    return 0;
}
