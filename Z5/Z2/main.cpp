//TP 2018/2019: Zadaća 5, Zadatak 2
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iterator>
class Padavine
{
    int max_iznos_velicine_padavina;
    std::vector<int> v_kolicine_padavina;
public:
    explicit Padavine(int vel)
    {
        if(vel<0)  throw std::range_error("Ilegalna maksimalna kolicina");
        max_iznos_velicine_padavina=vel;
    } // zabraniti koverziju int u objekte tipa padavine !?
    void RegistrirajPadavine(int kolicina)
    {
        if(kolicina<0 || kolicina>max_iznos_velicine_padavina)  throw std::range_error("Ilegalna kolicina padavina");
        v_kolicine_padavina.push_back(kolicina);
    }
    int DajBrojRegistriranihPadavina()  const
    {
        return v_kolicine_padavina.size();
    }
    void BrisiSve()
    {
        v_kolicine_padavina.resize(0);
    }
    int DajMinimalnuKolicinuPadavina()  const
    {
        if(!DajBrojRegistriranihPadavina()) throw std::range_error("Nema registriranih padavina");
        return *std::min_element(v_kolicine_padavina.begin(),v_kolicine_padavina.end(),[](int k1, int k2) {
            return k1<k2;
        });
    }
    int DajMaksimalnuKolicinuPadavina()  const
    {
        if(!DajBrojRegistriranihPadavina()) throw std::range_error("Nema registriranih padavina");
        return *std::max_element(v_kolicine_padavina.begin(),v_kolicine_padavina.end(),[](int k1, int k2) {
            return k1<k2;
        });
    }
    int DajBrojDanaSaPadavinamaVecimOd(int granica)  const
    {
        if(!DajBrojRegistriranihPadavina()) throw std::range_error("Nema registriranih padavina");
        return std::count_if(v_kolicine_padavina.begin(), v_kolicine_padavina.end(),std::bind(std::greater<int>(),std::placeholders::_1,granica));
    }
    /*void Ispisi_() const
    {
        Padavine tmp(max_iznos_velicine_padavina);
        tmp.v_kolicine_padavina=v_kolicine_padavina;
        std::sort(tmp.v_kolicine_padavina.begin(),tmp.v_kolicine_padavina.end(),std::greater<int>());
        std::for_each(tmp.v_kolicine_padavina.begin(),tmp.v_kolicine_padavina.end(), [](int p) {
            std::cout<<p<<std::endl;
        });
        //ko ce mu ga znat sta treba
    }*/
    void Ispisi()   const
    {
        Padavine tmp(max_iznos_velicine_padavina);
        tmp.v_kolicine_padavina=v_kolicine_padavina;
        std::sort(tmp.v_kolicine_padavina.begin(), tmp.v_kolicine_padavina.end(),std::greater<int>());
        std::copy(tmp.v_kolicine_padavina.begin(), tmp.v_kolicine_padavina.end(), std::ostream_iterator<int>(std::cout, "\n"));
    }
    int operator[](int i) const
    {
        if(i<1 || i>v_kolicine_padavina.size()) throw std::range_error("Neispravan indeks");
        return v_kolicine_padavina.at(i-1);
    }
    Padavine &operator ++()
    {
        max_iznos_velicine_padavina++;
        std::transform(v_kolicine_padavina.begin(), v_kolicine_padavina.end(), v_kolicine_padavina.begin(), std::bind(std::plus<int>(),std::placeholders::_1,1));
        return *this;
    }
    Padavine operator ++(int)
    {
        max_iznos_velicine_padavina++;
        auto tmp=*this;
        std::transform(v_kolicine_padavina.begin(), v_kolicine_padavina.end(), v_kolicine_padavina.begin(), std::bind(std::plus<int>(),std::placeholders::_1,1));
        return tmp;
    }
    friend Padavine operator +(const Padavine &p1, const Padavine &p2);
    friend Padavine operator -(const Padavine &p1, const Padavine &p2);
    friend Padavine operator +(const Padavine &p1, int n);
    friend Padavine operator +(int n, const Padavine &p1);
    friend Padavine operator -(const Padavine &p1, int n);
    friend Padavine operator -(int n, const Padavine &p1);
    friend Padavine operator +=(Padavine &p1, int n);
    friend Padavine operator +=(Padavine &p1, const Padavine &p2);
    friend Padavine operator -=(Padavine &p1, int n);
    friend Padavine operator -=(Padavine &p1, const Padavine &p2);
    Padavine operator -()
    {
        Padavine tmp(max_iznos_velicine_padavina);
        tmp.v_kolicine_padavina.resize(DajBrojRegistriranihPadavina());
        std::transform(v_kolicine_padavina.begin(), v_kolicine_padavina.end(),
        tmp.v_kolicine_padavina.begin(),std::bind(std::minus<int>(), max_iznos_velicine_padavina, std::placeholders::_1));
        return tmp;
    }
    friend bool operator ==(const Padavine &p1, const Padavine &p2);
    friend bool operator !=(const Padavine &p1, const Padavine &p2);
    operator int() =delete;

};
Padavine operator +(const Padavine &p1, int n)
{
    Padavine tmp(p1.max_iznos_velicine_padavina+n);
    tmp.v_kolicine_padavina.resize(p1.DajBrojRegistriranihPadavina());
    std::transform(p1.v_kolicine_padavina.begin(),p1.v_kolicine_padavina.end(), 
    tmp.v_kolicine_padavina.begin(),std::bind(std::plus<int>(), n, std::placeholders::_1));
    return tmp;
}
Padavine operator +(int n, const Padavine &p1)
{
    Padavine tmp(p1.max_iznos_velicine_padavina+n);
    tmp.v_kolicine_padavina.resize(p1.DajBrojRegistriranihPadavina());
    std::transform(p1.v_kolicine_padavina.begin(),p1.v_kolicine_padavina.end(), 
    tmp.v_kolicine_padavina.begin(),std::bind(std::plus<int>(), n, std::placeholders::_1));
    return tmp;
}
Padavine operator -(const Padavine &p1, int n)
{
    if(n>p1.DajMinimalnuKolicinuPadavina()) throw std::domain_error("Nekorektan rezultat operacije");
    Padavine tmp(p1.max_iznos_velicine_padavina-n);
    tmp.v_kolicine_padavina.resize(p1.DajBrojRegistriranihPadavina());
    std::transform(p1.v_kolicine_padavina.begin(),p1.v_kolicine_padavina.end(), tmp.v_kolicine_padavina.begin(),
    std::bind(std::minus<int>(),std::placeholders::_1,n));
    return tmp;
}
Padavine operator -(int n, const Padavine &p1)
{
    if(n<p1.DajMaksimalnuKolicinuPadavina()) throw std::domain_error("Nekorektan rezultat operacije");
    Padavine tmp(n);
    tmp.v_kolicine_padavina.resize(p1.DajBrojRegistriranihPadavina());
    std::transform(p1.v_kolicine_padavina.begin(),p1.v_kolicine_padavina.end(),
    tmp.v_kolicine_padavina.begin(),std::bind(std::minus<int>(), n, std::placeholders::_1));
    return tmp;
}
Padavine operator +=(Padavine &p1, int n)
{
    p1=p1+n;
    return p1;
}
Padavine operator +=(Padavine &p1, const Padavine &p2)
{
    p1=p1+p2;
    return p1;
}
Padavine operator -=(Padavine &p1, int n)
{
    p1=p1-n;
    return p1;
}
Padavine operator -=(Padavine &p1, const Padavine &p2)
{
    p1=p1-p2;
    return p1;
}
Padavine operator +(const Padavine &p1, const Padavine &p2)
{
    if(p1.DajBrojRegistriranihPadavina()!=p2.DajBrojRegistriranihPadavina())    throw std::domain_error("Nesaglasni operandi");
    Padavine tmp(p1.max_iznos_velicine_padavina);
    tmp.v_kolicine_padavina.resize(p1.v_kolicine_padavina.size());
    std::transform(p1.v_kolicine_padavina.begin(),p1.v_kolicine_padavina.end(),p2.v_kolicine_padavina.begin(),tmp.v_kolicine_padavina.begin(),std::plus<int>());
    if(tmp.DajMaksimalnuKolicinuPadavina()>tmp.max_iznos_velicine_padavina) throw std::domain_error("Nesaglasni operandi");
    return tmp;
}
Padavine operator -(const Padavine &p1, const Padavine &p2)
{
    if(p1.DajBrojRegistriranihPadavina()!=p2.DajBrojRegistriranihPadavina())    throw std::domain_error("Nesaglasni operandi");
    Padavine tmp(p1.max_iznos_velicine_padavina);
    tmp.v_kolicine_padavina.resize(p1.v_kolicine_padavina.size());
    std::transform(p1.v_kolicine_padavina.begin(),p1.v_kolicine_padavina.end(),
                   p2.v_kolicine_padavina.begin(),tmp.v_kolicine_padavina.begin(),std::minus<int>());
    if(tmp.DajMinimalnuKolicinuPadavina()<0) throw std::domain_error("Nesaglasni operandi");
    return tmp;
}
bool operator ==(const Padavine &p1, const Padavine &p2)
{
    if(p1.DajBrojRegistriranihPadavina()!=p2.DajBrojRegistriranihPadavina())    return false;
    return std::equal(p1.v_kolicine_padavina.begin(),p1.v_kolicine_padavina.end(),p2.v_kolicine_padavina.begin());
}
bool operator !=(const Padavine &p1, const Padavine &p2)
{
    return !(p1==p2);
}
int main ()
{
    Padavine t(10);
    for(int i= 5; i<=10; i++) {
        t.RegistrirajPadavine(i);
    }
    (-t).Ispisi();
}