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
template<typename nekiTip>
std::set<nekiTip> operator *(std::set<nekiTip> A,std::set<nekiTip> B)
{
	std::set<nekiTip> presjek;
	for(auto x : A) {
		if(B.count(x)) presjek.insert(x);
	}
	return presjek;
}
template <typename nekiTip>
std::set<nekiTip> operator +(std::set<nekiTip> A,std::set<nekiTip> B)
{
	std::set<nekiTip> unija;
	for(auto x : A) unija.insert(x);
	for(auto x : B) unija.insert(x);
	return unija;
}
template <typename nekiTip>
std::ostream &operator <<(std::ostream &tok, const std::set<nekiTip> &set)
{
	tok<<"{";
	for(auto it=set.begin(); it!=set.end(); it++) {
		tok<<*it;
		if(it!=--set.end())
			tok<<",";
	}
	tok<<"}";
	return tok;
}
template <typename nekiTip>
std::set<nekiTip> operator +=(std::set<nekiTip> &A,std::set<nekiTip> B)
{
	for(auto x : B) A.insert(x);
	return A;
}
template <typename nekiTip>
std::set<nekiTip> operator *=(std::set<nekiTip> &A,std::set<nekiTip> B)
{
	std::set<nekiTip> pomocni;
	for(auto x : A)
		if(B.count(x))
			pomocni.insert(x);
	A=pomocni;
	return A;
}
template <typename nekiTip, typename nekiTip2>
std::set<std::pair<nekiTip,nekiTip2>> operator %(std::set<nekiTip> A, std::set<nekiTip2> B)
{
	std::set<std::pair<nekiTip,nekiTip2>> izlaz;
	for(auto x : A)
		for(auto y : B)
			izlaz.insert(std::make_pair(x,y));
	return izlaz;
}
template <typename nekiTip, typename nekiTip2>
std::ostream &operator <<(std::ostream &tok, const std::set<std::pair<nekiTip,nekiTip2>> &setParova)
{
	tok<<"{";
	for(auto x=setParova.begin(); x!=setParova.end(); x++) {
		tok<<"("<<x->first<<","<<x->second<<")";
		if(x!=--setParova.end())
			tok<<",";
	}
	tok<<"}";
	return tok;
}
int main ()
{
	std::set<char> s3{'A', 'B'};
	std::set<int> s4{1, 2, 3};
	std::cout << s3 % s4 << std::endl;
	return 0;
}
