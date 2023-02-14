#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <memory>
#define x first
#define y second
typedef std::pair<double, double> Tacka;
enum Pozicija {GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno};
enum Smjer {Nalijevo, Nadesno};
class NepreklapajuciPravougaonik
{
    Tacka dLijevo, gDesno;
    NepreklapajuciPravougaonik *prethodni;
    static NepreklapajuciPravougaonik *zadnji;
    void PreklapajuLiSe(const Tacka &t1, const Tacka &t2);
public:
    NepreklapajuciPravougaonik(const Tacka &t1, const Tacka &t2)
    {
        Postavi(t1,t2);
        prethodni=zadnji;
        zadnji=this;
    }
    NepreklapajuciPravougaonik(const NepreklapajuciPravougaonik &P) =delete;
    NepreklapajuciPravougaonik &operator = (const NepreklapajuciPravougaonik &P) =delete;
    ~NepreklapajuciPravougaonik();
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
    void Transliraj(double delta_x, double delta_y)
    {
        Tacka dLijevo_tmp,gDesno_tmp;
        dLijevo_tmp.x =DajTjeme(DoljeLijevo).x+ delta_x;
        dLijevo_tmp.y =DajTjeme(DoljeLijevo).y+delta_y;
        gDesno_tmp.x =DajTjeme(GoreDesno).x+ delta_x;
        gDesno_tmp.y =DajTjeme(GoreDesno).y+delta_y;
        Postavi(dLijevo_tmp,gDesno_tmp);
    }
    void Rotiraj(const Tacka &t, Smjer s);
    void Ispisi() const
    {
        std::cout << "{{" << DajTjeme(GoreLijevo).x << "," << DajTjeme(GoreLijevo).y << "},{"
                  << DajTjeme(DoljeDesno).x << "," << DajTjeme(DoljeDesno).y << "}}";
    }
    friend bool DaLiSePoklapaju(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
    friend bool DaLiSuPodudarni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
    friend bool DaLiSuSlicni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
};
NepreklapajuciPravougaonik* NepreklapajuciPravougaonik::zadnji=nullptr;
NepreklapajuciPravougaonik::~NepreklapajuciPravougaonik()
{
    NepreklapajuciPravougaonik *pok=zadnji;
    if(pok==this)
        zadnji=prethodni;
    else {
        while(pok->prethodni!=this)
            pok=pok->prethodni;
        pok->prethodni=prethodni;
    }
}
void NepreklapajuciPravougaonik::PreklapajuLiSe(const Tacka &t1, const Tacka &t2)
{
    auto pok=zadnji;
    while(pok) {
        if(std::max(t1.x,pok->DajTjeme(DoljeLijevo).x)< std::min(t2.x,pok->DajTjeme(GoreDesno).x) &&
                std::max(t1.y,pok->DajTjeme(DoljeLijevo).y)<std::min(t2.y,pok->DajTjeme(GoreDesno).y))
            throw std::logic_error("Nedozvoljeno preklapanje");
        pok=pok->prethodni;
    }
}
void NepreklapajuciPravougaonik::Postavi(const Tacka &t1, const Tacka &t2)
{
    PreklapajuLiSe({std::min(t1.x, t2.x), std::min(t1.y, t2.y)}, {std::max(t1.x, t2.x), std::max(t1.y, t2.y)});
    dLijevo= {std::min(t1.x, t2.x), std::min(t1.y, t2.y)};
    gDesno= {std::max(t1.x, t2.x), std::max(t1.y, t2.y)};
}
void NepreklapajuciPravougaonik::Postavi(Pozicija p, const Tacka &t)
{
    Tacka gDesno_tmp(DajTjeme(GoreDesno)),dLijevo_tmp=DajTjeme(DoljeLijevo);
    if(p == GoreDesno) gDesno_tmp = t;
    if(p == DoljeLijevo) dLijevo_tmp = t;
    if(p == GoreLijevo) dLijevo_tmp.x = t.x, gDesno_tmp.y = t.y;
    if(p == DoljeDesno) gDesno_tmp.x = t.x, dLijevo_tmp.y = t.y;
    Postavi(dLijevo_tmp,gDesno_tmp);
}
void NepreklapajuciPravougaonik::Centriraj(const Tacka &t)
{
    double horizontalna=DajHorizontalnu(),vertikalna=DajVertikalnu();
    Tacka dLijevo_tmp = {t.x - horizontalna / 2, t.y - vertikalna / 2};
    Tacka gDesno_tmp = {t.x + horizontalna / 2, t.y + vertikalna / 2};
    Postavi(dLijevo_tmp,gDesno_tmp);
}
Tacka NepreklapajuciPravougaonik::DajTjeme(Pozicija p) const
{
    if(p == GoreLijevo) return {dLijevo.x, gDesno.y};
    if(p == GoreDesno) return gDesno;
    if(p == DoljeDesno) return {gDesno.x, dLijevo.y};
    if(p == DoljeLijevo) return dLijevo;
}
void NepreklapajuciPravougaonik::Rotiraj(const Tacka &t, Smjer s)
{
    Tacka dLijevo_tmp,gDesno_tmp;
    if(s==Nadesno) {
        dLijevo_tmp.x = t.x + (DajTjeme(DoljeLijevo).y - t.y);
        dLijevo_tmp.y = t.y - (DajTjeme(DoljeLijevo).x - t.x);
        gDesno_tmp.x = t.x + (DajTjeme(GoreDesno).y - t.y);
        gDesno_tmp.y = t.y - (DajTjeme(GoreDesno).x - t.x);
    }
    if(s==Nalijevo) {
        dLijevo_tmp.x = t.x - (DajTjeme(DoljeLijevo).y - t.y);
        dLijevo_tmp.y = t.y + (DajTjeme(DoljeLijevo).x - t.x);
        gDesno_tmp.x = t.x - (DajTjeme(GoreDesno).y - t.y);
        gDesno_tmp.y = t.y + (DajTjeme(GoreDesno).x - t.x);
    }
    Postavi(dLijevo_tmp,gDesno_tmp);
}
bool DaLiSePoklapaju(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2) // uvijek vraća false !?
{
    return p1.DajTjeme(DoljeLijevo).x == p2.DajTjeme(DoljeLijevo).x && p1.DajTjeme(GoreDesno).x == p2.DajTjeme(GoreDesno).x
           && p1.DajTjeme(DoljeLijevo).y == p2.DajTjeme(DoljeLijevo).y && p1.DajTjeme(GoreDesno).y == p2.DajTjeme(GoreDesno).y;
}
bool DaLiSuPodudarni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2)
{
    return p1.DajHorizontalnu() == p2.DajHorizontalnu() && p1.DajVertikalnu() == p2.DajVertikalnu() ||
           p1.DajHorizontalnu() == p2.DajVertikalnu() &&p1.DajVertikalnu() == p2.DajHorizontalnu();
}
bool DaLiSuSlicni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2)
{
    return p1.DajHorizontalnu() / p2.DajHorizontalnu()  == p1.DajVertikalnu() / p2.DajVertikalnu()||
           p1.DajHorizontalnu() / p2.DajVertikalnu()  == p1.DajVertikalnu() / p2.DajHorizontalnu();
}
int main()
{
    int n;
    std::cout<<"Unesite n: ";
    std::cin>>n;
    std::vector<std::shared_ptr<NepreklapajuciPravougaonik>> vPravougaonika;
    for(int i=0; i<n; i++) {
        double x1,x2,y1,y2;
        std::cout<<"Unesite 1. tjeme pravougaonika "<<i+1<<": ";
        std::cin>>x1>>y1;
        std::cout<<"Unesite 2. tjeme pravougaonika "<<i+1<<": ";
        std::cin>>x2>>y2;
        try {
            std::shared_ptr<NepreklapajuciPravougaonik> P = std::make_shared<NepreklapajuciPravougaonik>(std::make_pair(x1,y1),std::make_pair(x2,y2));
            vPravougaonika.push_back(P);
        } catch(std::logic_error e) {
            std::cout<<"GRESKA: "<<e.what()<<"! Ponovite unos: "<<std::endl;
            i--;
            throw;
        }
    }
    std::sort(vPravougaonika.begin(),vPravougaonika.end(),[](std::shared_ptr<NepreklapajuciPravougaonik> P1, std::shared_ptr<NepreklapajuciPravougaonik> P2) {
        return P1->DajPovrsinu()<P2->DajPovrsinu();
    });
    std::cout<<"Ispis pravougaonika nakon sortiranja: "<<std::endl;
    std::for_each(vPravougaonika.begin(),vPravougaonika.end(),[](std::shared_ptr<NepreklapajuciPravougaonik> P) {
        P->Ispisi();
        std::cout<<std::endl;
    });
    std::cout<<"Podudarni pravougaonici: "<<std::endl;
    bool postoje=false;
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if(DaLiSuPodudarni(*vPravougaonika[i],*vPravougaonika[j])) {
                postoje=true;
                vPravougaonika[i]->Ispisi();
                std::cout<<" i ";
                vPravougaonika[j]->Ispisi();
                std::cout<<std::endl;
            }
    if(!postoje)
        std::cout<<"Nema podudarnih pravougaonika.";
    return 0;
}
