#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string ZamjenaRijeci(std::string s, std::vector<std::string> v1,
                          std::vector<std::string> v2)
{
    if (int(v1.size()) != int(v2.size()))
        throw std::domain_error("Nekorektni parametri");
    bool razmak = true;
    int br = 0;
    std::string novi, razmaci, rijeci, temp;
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) == ' ' && br == 0)
            novi.push_back(s.at(i)); // pocetak
        if (s.at(i) == ' ') {
            razmak = true;
            razmaci.push_back(s.at(i));
            if (br != 0) { // naidje se na rijec
                for (int j = 0; j < int(v1.size()); j++) {
                    std::string clan_prvog = v1.at(j);
                    std::string clan_drugog = v2.at(j);
                    if (rijeci == clan_prvog) {
                        temp = rijeci;
                        rijeci = clan_drugog;
                        clan_drugog = temp;
                        novi = novi + rijeci + razmaci;
                        break;
                    }
                    if (rijeci != clan_prvog && j == int(v1.size()) - 1)
                        novi = novi + rijeci + razmaci;
                }
            }
            rijeci = "";
            razmaci = "";
        } else if (razmak) {
            razmak = false;
            br++;
        }
        if (s.at(i) != ' ')
            rijeci.push_back(s.at(i));
        // ako se dodje do kraja stringa
        if (i == s.length() - 1) {
            if (br != 0) {
                for (int j = 0; j < int(v1.size()); j++) {
                    std::string clan_prvog = v1.at(j);
                    std::string clan_drugog = v2.at(j);
                    if (rijeci == clan_prvog) {
                        temp = rijeci;
                        rijeci = clan_drugog;
                        clan_drugog = temp;
                        novi = novi + rijeci;
                        break;
                    }
                    if (rijeci != clan_prvog && j == int(v1.size()) - 1)
                        novi = novi + rijeci;
                }
            }
        }
    }
    return novi;
}

int main()
{
    int n;
    std::cout << "Unesite koliko riječi sadrži rječnik." << std::endl;
    std::cin >> n;
    std::cin.ignore(10000, '\n');
    char original[50], zamjena[50];
    std::vector<std::string> v1, v2;
    for (int i = 0; i < n; i++) {
        std::cout << "Unesite " << i + 1 << ". original rječnika." << std::endl;
        std::cin >> original;
        v1.push_back(original);
        std::cout << "Unesite " << i + 1 << ". zamjenu rječnika." << std::endl;
        std::cin >> zamjena;
        v2.push_back(zamjena);
    }
    std::cin.ignore(10000, '\n');
    for (;;) {
        std::cout << "Unesite rečenicu koju želite transformisati: " << std::endl;
        std::string recenica;
        std::getline(std::cin, recenica);
        if(!recenica.length()) return 1;
        std::string nova_recenica = ZamjenaRijeci(recenica, v1, v2);
        std::cout << "Transformisana rečenica glasi:" << std::endl;
        for (int i = 0; i < nova_recenica.length(); i++) {
            std::cout << nova_recenica.at(i);
        }
        std::cout << std::endl;
    }
    return 0;
}
