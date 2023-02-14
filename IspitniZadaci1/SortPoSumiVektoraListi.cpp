#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
int main()
{
    std::vector<std::list<int>> v;
    v.push_back({1,2,3,4,5});
    v.push_back({2,2,2,2,2});
    v.push_back({5,4,3,4,5});
    v.push_back({10,10,10,10,10});
    //
    std::sort(v.begin(),v.end(),[](std::list<int> l1, std::list<int> l2) {
        int suma1=0;
        int suma2=0;
        for(auto it=l1.begin(); it!=l1.end(); it++) {
            suma1+=*it;
        }
        for(auto it=l2.begin(); it!=l2.end(); it++) {
            suma2+=*it;
        }
        return suma1<suma2;
    });
    for(int i=0; i<v.size(); i++) {
        for(auto it=v.at(i).begin(); it!=v.at(i).end(); it++) {
            std::cout<<*it<<" ";
        }
        std::cout<<"\n";
    }
    return 0;
}
