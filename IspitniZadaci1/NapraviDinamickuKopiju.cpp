#include<iostream>
#include<vector>
#include<stack>
int **NapraviDinamickuKopiju(std::vector<std::stack<int>> v)
{
    int **kopija=nullptr;
    int brojac=0;
    for(int i=0; i<v.size(); i++)
        brojac+=v.at(i).size();
    try {
        kopija=new int*[v.size()];
        try {
            kopija[0]=new int[brojac];
            for(int i=1; i<v.size(); i++)
                kopija[i]=kopija[i-1]+v.at(i).size();
            for(int i=0; i<v.size(); i++) {
                int j=v.at(i).size()-1;
                while(!v.at(i).empty()) {
                    kopija[i][j]=v.at(i).top();
                    v.at(i).pop();
                    j--;
                    //ruzni stackovi do mile majke, valjda je ovo ok
                }
            }
        } catch(...) {
            delete[] kopija[0];
            throw;
        }
    } catch(...) {
        delete[] kopija;
        throw;
    }
    return kopija;
}
int main()
{
    int n;
    std::cout<<"Broj stekova: ";
    std::cin>>n;
    //treba i ovdje neki try ubaciti ako ne bi bilo memorije za n stekova
    std::vector<std::stack<int>> v(n);
    for(int i=0; i<n; i++) {
        std::cout<<"Elementi "<<i+1<<". steka (0 za kraj) : ";
        for(;;) {
            int a;
            std::cin>>a;
            v.at(i).push(a);
            if(!a)  break;
        }
    }
    try {
        int** kopija=NapraviDinamickuKopiju(v);
        if(!kopija) {
            std::cout<<"nullptr";
            return 0;
        } //provjere radi :D
        std::cout<<"Kreirana matrica:\n";
        for(int i=0; i<n; i++) {
            for(int j=0;; j++) {
                std::cout<<kopija[i][j]<<" ";
                if(!kopija[i][j])   break;
            }
            std::cout<<"\n";
        }
        delete[] kopija[0];
        delete[] kopija;
    } catch(...) {
        std::cout<<"Nedovoljno memorije";
    }
    return 0;
}
//radi i ovaj sada, malo je ruzan, moze i ljepse