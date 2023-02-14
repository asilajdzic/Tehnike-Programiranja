/* 
    TP 16/17 (Tutorijal 7, Zadatak 7)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <set>
#include <string>
template <typename nekiTip>
auto Unija(std::set<nekiTip> A,std::set<nekiTip> B) ->std::set<nekiTip>
{
	std::set<nekiTip> unija;
	for(auto x : A) unija.insert(x);
	for(auto x : B) unija.insert(x);
	return unija;
}
template<typename nekiTip>
auto Presjek(std::set<nekiTip> A,std::set<nekiTip> B) ->std::set<nekiTip>
{
	std::set<nekiTip> presjek;
	for(auto x : A)
	{
		if(B.count(x)) presjek.insert(x);
	}
	
	return presjek;
}
int main ()
{
	std::set<std::string> A {"Adin","Dina","Nida","Inad","Dani"};
	std::set<std::string> B {"Dina","Nida","Inad","Dani","TP"};
	auto unija=Unija(A,B);
	auto presjek=Presjek(A,B);
	for(auto x : unija) std::cout<<x<<"\n";
	std::cout<<"-----------\n";
	for(auto x : presjek) std::cout<<x<<"\n";
	return 0;
}