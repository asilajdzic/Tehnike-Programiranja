#include <iostream>
#include <vector>
#include <deque>
#include <iterator>

template<class input, class output, class kriterij>
auto PopuniPoKriteriju(input poc1,input kraj1, output poc2, output kraj2, kriterij funkcija)   -> decltype(*poc1+*poc1)
{
    kraj2=poc2;
    decltype(*poc1+*poc1) suma=0;
    while(poc1!=kraj1) {
        suma+=*poc1;
        *kraj2++=funkcija(*poc1++);
    }
    return suma;
}
int main()
{
    std::vector<int> v(10);
    std::deque<int> d(10);
    for(int i=0; i<10; i++)
        std::cin>>v.at(i);
    auto suma=PopuniPoKriteriju(v.begin(),v.end(),d.rbegin(),d.rend(),[](int n) {
        return n*n;
    });
    for(int i=0; i<10; i++)
        std::cout<<d.at(i)<<" ";
    std::cout<<"\n"<<suma;
    //ne znam ovaj dio sa p4 kako da uradim :D, nesto imam belaja sa referencom kad saljem
    //ali bio je jedan u zadaci sto je nesta slicno trebalo pa bi mogli tu pogledati
    return 0;
}
