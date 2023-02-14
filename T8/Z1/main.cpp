//TP 2018/2019: Tutorijal 8, Zadatak 1
#include <iostream>
#include <iomanip>
struct Vrijeme {
    int sati;
    int minute;
    int sekunde;
};
void TestirajVrijeme(Vrijeme vrijeme)
{
    if(vrijeme.sati<0 || vrijeme.sati>23 || vrijeme.minute<0 || vrijeme.minute>59 || vrijeme.sekunde<0 || vrijeme.sekunde>59)
        throw std::domain_error("Neispravno vrijeme");
}
void UnesiVrijeme(Vrijeme &v1)
{
    std::cin>>v1.sati>>v1.minute>>v1.sekunde;
    TestirajVrijeme(v1);
}
void IspisiVrijeme(Vrijeme vrijeme)
{
    TestirajVrijeme(vrijeme);
    std::cout<<std::setfill('0')<<std::setw(2)<<vrijeme.sati<<":"<<std::setfill('0')<<std::setw(2)<<vrijeme.minute<<":"<<std::setfill('0')<<std::setw(2)<<vrijeme.sekunde<<std::endl;
}
Vrijeme SaberiVrijeme(Vrijeme v1, Vrijeme v2)
{
    TestirajVrijeme(v1);
    TestirajVrijeme(v2);
    Vrijeme vrijeme;
    vrijeme.sati=v1.sati+v2.sati;
    vrijeme.minute=v2.minute+v1.minute;
    vrijeme.sekunde=v1.sekunde+v2.sekunde;
    vrijeme.minute+=vrijeme.sekunde/60;
    vrijeme.sati+=vrijeme.minute/60;
    vrijeme.sekunde=vrijeme.sekunde%60;
    vrijeme.minute=vrijeme.minute%60;
    vrijeme.sati=vrijeme.sati%24;
    return vrijeme;
}
int main ()
{
    Vrijeme v1,v2;
    try {
        std::cout<<"Unesite prvo vrijeme (h m s): ";
        UnesiVrijeme(v1);
        std::cout<<"Unesite drugo vrijeme (h m s): ";
        UnesiVrijeme(v2);
        std::cout<<"Prvo vrijeme: ";
        IspisiVrijeme(v1);
        std::cout<<"Drugo vrijeme: ";
        IspisiVrijeme(v2);
        std::cout<<"Zbir vremena: ";
        IspisiVrijeme(SaberiVrijeme(v1,v2));
    } catch(std::domain_error dp) {
        std::cout<<dp.what();
    }
    return 0;
}