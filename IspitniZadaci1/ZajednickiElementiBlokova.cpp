#include <array>
#include <deque>
#include <iostream>
#include <vector>

template <typename NekiTip1, typename NekiTip2, typename NekiTip>
NekiTip ZajednickiElementiBlokova(NekiTip1 p1, NekiTip1 p2, NekiTip2 p3,NekiTip2 p4, NekiTip p5)
{
    NekiTip2 pocetak_drugog = p3;
    NekiTip pocetak=p5;
    while (p1 != p2) {
        while (p3 != p4) {
            if (*p1 == *p3) {
                bool treba=true;
                NekiTip tmp=pocetak;
                while(tmp!=p5) {
                    if(*tmp==*p1) treba=false;
                    tmp++;
                }
                if(treba) {
                    *p5 = *p1;
                    p5++;
                }
            }
            p3++;
        }
        p3 = pocetak_drugog;
        p1++;
    }
    return p5;
}
int main()
{
    std::cout << "Unesi broj elemenata niza (ne vise od 100): ";
    int n, d;
    std::cin >> n;
    std::array<int, 100> niz;
    std::cout << std::endl << "Unesi elemente niza: ";
    for (int i = 0; i < n; i++) {
        std::cin >> niz.at(i);
    }
    std::cout << "Unesi broj elemenata deka: ";
    std::cin >> d;
    std::deque<double> dek;
    double unos_za_dek;
    std::cout << std::endl << "Unesi elemente deka: ";
    for (int i = 0; i < d; i++) {
        std::cin >> unos_za_dek;
        dek.push_back(unos_za_dek);
    }
    int min;
    if (n <= d)
        min = n;
    else
        min = d;
    std::vector<int> v(min);
    auto p = ZajednickiElementiBlokova(niz.begin(), niz.begin()+n, dek.begin(), dek.end(), v.begin());
    v.resize(p - v.begin());
    int vel = v.size();
    std::cout << std::endl
              << "Vektor zajednickih elemenata niza i deka ima " << vel
              << " elemenata" << std::endl;
    std::cout << "Zajednicki elementi glase: ";
    for (int i = 0; i < vel; i++) {
        std::cout << v.at(i);
    }
    return 0;
}
