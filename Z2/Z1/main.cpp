//TP 2018/2019: Zadaća 2, Zadatak 1
#include <iostream>
#include <vector>
std::vector<std::vector<std::vector<char>>> KreirajMatrice(int m, int n)
{
    std::vector<std::vector<std::vector<char>>> matrice(2,std::vector<std::vector<char>>(m,std::vector<char>(n,'-')));
    return matrice;
} // dobra
void Unos(std::vector<std::vector<std::vector<char>>> &matrice, int p)
{
    char znak='0';
    for(int i=0; i<p; i++) {
        int x1,x2,y1,y2;
        std::cout<<"Naida unesi pocetne i krajnje koordinate "<<i+1<<". robota:\n";
        std::cin>>x1>>y1;
        std::cin>>x2>>y2;
        if(x1==x2 && abs(y1-y2)==i) {
            for(int j=y1; j<=y2; j++) {
                matrice.at(0).at(x1).at(j)=znak;
            }
        }
        if(y1==y2 && abs(x1-x2)==i && i!=0) {
            for(int j=x1; j<=x2; j++) {
                matrice.at(0).at(j).at(y1)=znak;
            }
        }
        std::cout<<"Alina unesi pocetne i krajnje koordinate "<<i+1<<". robota:\n";
        std::cin>>x1>>y1;
        std::cin>>x2>>y2;
        if(x1==x2 && abs(y1-y2)==i) {
            for(int j=y1; j<=y2; j++) {
                matrice.at(1).at(x1).at(j)=znak;
            }
        }
        if(y1==y2 && abs(x1-x2)==i && i!=0) {
            for(int j=x1; j<=x2; j++) {
                matrice.at(1).at(j).at(y1)=znak;
            }
        }
        znak++;
    }
}
int main ()
{
    std::cout<<"Igra je pocela, unesite dimenzije matrica (dva broja):\n";
    int m, n;
    std::cin>>m>>n;
    auto matrice=KreirajMatrice(m,n);
    int brRobota;
    std::cout<<"Unesite broj robota:\n";
    std::cin>>brRobota;
    Unos(matrice, brRobota);
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++)
            std::cout<<matrice.at(0).at(i).at(j)<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n\n";
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++)
            std::cout<<matrice.at(1).at(i).at(j)<<" ";
        std::cout<<"\n";
    }
    return 0;
}
