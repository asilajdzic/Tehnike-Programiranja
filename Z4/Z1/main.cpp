#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#define x first
#define y second
typedef std::pair<double, double> Tacka;
enum Pozicija {GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno};
enum Smjer {Nalijevo, Nadesno};
class Pravougaonik
{
    Tacka dLijevo, gDesno;
public:
    Pravougaonik(const Tacka &t1, const Tacka &t2)
    {
        Postavi(t1,t2);
    }
    void Postavi(const Tacka &t1, const Tacka &t2);
    void Postavi(Pozicija p, const Tacka &t);
    void Centriraj(const Tacka &t);
    Tacka DajTjeme(Pozicija p) const;
    Tacka DajCentar() const
    {
        return {(gDesno.x + dLijevo.x) / 2, (gDesno.y + dLijevo.y) / 2};
    }
    double DajHorizontalnu() const
    {
        return gDesno.x - dLijevo.x;
    }
    double DajVertikalnu() const
    {
        return gDesno.y - dLijevo.y;
    }
    double DajObim() const
    {
        return 2 * (DajHorizontalnu() + DajVertikalnu());
    }
    double DajPovrsinu() const
    {
        return DajHorizontalnu() * DajVertikalnu();
    }
    static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2);
    void Transliraj(double delta_x, double delta_y)
    {
        dLijevo.x += delta_x;
        dLijevo.y += delta_y;
        gDesno.x += delta_x;
        gDesno.y += delta_y;
    }
    void Rotiraj(const Tacka &t, Smjer s);
    void Ispisi() const
    {
        std::cout << "{{" << DajTjeme(GoreLijevo).x << "," << DajTjeme(GoreLijevo).y << "},{"
                  << DajTjeme(DoljeDesno).x << "," << DajTjeme(DoljeDesno).y << "}}";
    }
    friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
};
void Pravougaonik::Postavi(const Tacka &t1, const Tacka &t2)
{
    dLijevo= {std::min(t1.x, t2.x), std::min(t1.y, t2.y)};
    gDesno= {std::max(t1.x, t2.x), std::max(t1.y, t2.y)};
}
void Pravougaonik::Postavi(Pozicija p, const Tacka &t)
{
    if(p == GoreDesno) gDesno = t;
    if(p == DoljeLijevo) dLijevo = t;
    if(p == GoreLijevo) dLijevo.x = t.x, gDesno.y = t.y;
    if(p == DoljeDesno) gDesno.x = t.x, dLijevo.y = t.y;
}
void Pravougaonik::Centriraj(const Tacka &t)
{
    double horizontalna=DajHorizontalnu(), vertikalna=DajVertikalnu();
    dLijevo = {t.x - horizontalna / 2, t.y - vertikalna / 2};
    gDesno = {t.x + horizontalna / 2, t.y + vertikalna / 2};
    *this=Pravougaonik(dLijevo,gDesno);
}
Tacka Pravougaonik::DajTjeme(Pozicija p) const
{
    if(p == GoreLijevo) return {dLijevo.x, gDesno.y};
    if(p == GoreDesno) return gDesno;
    if(p == DoljeDesno) return {gDesno.x, dLijevo.y};
    if(p == DoljeLijevo) return dLijevo;
}
Pravougaonik Pravougaonik::Presjek(const Pravougaonik &p1, const Pravougaonik &p2)
{
    if(std::max(p1.dLijevo.x, p2.dLijevo.x) > std::min(p1.gDesno.x, p2.gDesno.x) ||
            std::max(p1.dLijevo.y, p2.dLijevo.y) > std::min(p1.gDesno.y, p2.gDesno.y))
        throw std::domain_error("Pravougaonici se ne presjecaju");
    return Pravougaonik({std::max(p1.dLijevo.x, p2.dLijevo.x), std::max(p1.dLijevo.y, p2.dLijevo.y)},
    {std::min(p1.gDesno.x, p2.gDesno.x), std::min(p1.gDesno.y, p2.gDesno.y)});
}
void Pravougaonik::Rotiraj(const Tacka &t, Smjer s)
{
    Tacka temp_dl(dLijevo), temp_gd(gDesno);
    if(s==Nadesno) {
        dLijevo.x = t.x + (temp_dl.y - t.y);
        dLijevo.y = t.y - (temp_dl.x - t.x);
        gDesno.x = t.x + (temp_gd.y - t.y);
        gDesno.y = t.y - (temp_gd.x - t.x);
    }
    if(s==Nalijevo) {
        dLijevo.x = t.x - (temp_dl.y - t.y);
        dLijevo.y = t.y + (temp_dl.x - t.x);
        gDesno.x = t.x - (temp_gd.y - t.y);
        gDesno.y = t.y + (temp_gd.x - t.x);
    }
    *this = Pravougaonik(dLijevo, gDesno);
}
bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2)
{
    return p1.DajTjeme(DoljeLijevo).x == p2.DajTjeme(DoljeLijevo).x && p1.DajTjeme(GoreDesno).x == p2.DajTjeme(GoreDesno).x
           && p1.DajTjeme(DoljeLijevo).y == p2.DajTjeme(DoljeLijevo).y && p1.DajTjeme(GoreDesno).y == p2.DajTjeme(GoreDesno).y;
}
bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2)
{
    return p1.DajHorizontalnu() == p2.DajHorizontalnu() && p1.DajVertikalnu() == p2.DajVertikalnu() ||
           p1.DajHorizontalnu() == p2.DajVertikalnu() &&p1.DajVertikalnu() == p2.DajHorizontalnu();
}
bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2)
{
    return p1.DajHorizontalnu() / p2.DajHorizontalnu()  == p1.DajVertikalnu() / p2.DajVertikalnu()||
           p1.DajHorizontalnu() / p2.DajVertikalnu()  == p1.DajVertikalnu() / p2.DajHorizontalnu();
}
int main()
{
    int n;
    std::cout<<"Unesite n: ";
    std::cin>>n;
    Pravougaonik **nizPravougaonika=new Pravougaonik*[n];
    try {
        for(int i=0; i<n; i++) {
            double x1,x2,y1,y2;
            std::cout<<"Unesite 1. tjeme pravougaonika "<<i+1<<": ";
            std::cin>>x1>>y1;
            std::cout<<"Unesite 2. tjeme pravougaonika "<<i+1<<": ";
            std::cin>>x2>>y2;
            nizPravougaonika[i]=new Pravougaonik({x1,y1}, {x2,y2});
        }
    } catch(...) {
        for(int i=0; i<n; i++)    delete nizPravougaonika[i];
        delete[] nizPravougaonika;
    }
    std::cout<<"Unesite podatke za transliranje (dx dy): ";
    double delta_x,delta_y;
    std::cin>>delta_x>>delta_y;
    std::transform(nizPravougaonika,nizPravougaonika+n,nizPravougaonika,[delta_x,delta_y](Pravougaonik *P) {
        P->Transliraj(delta_x,delta_y);
        P->Rotiraj(P->DajCentar(),Nadesno);
        return P;
    });
    std::cout<<"Pravougaonici, nakon transformacija:\n";
    std::for_each(nizPravougaonika,nizPravougaonika+n,[](Pravougaonik *P) {
        P->Ispisi();
        std::cout<<std::endl;
    });
    std::cout<<"Pravougaonik s najvecom povrsinom: ";
    (*std::max_element(nizPravougaonika,nizPravougaonika+n,[](Pravougaonik *P1, Pravougaonik *P2) {
        return P1->DajPovrsinu()<P2->DajPovrsinu();
    }))->Ispisi();
    for(int i=0; i<n; i++)    delete nizPravougaonika[i];
    delete[] nizPravougaonika;
    return 0;
}