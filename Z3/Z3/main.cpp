//TP 2018/2019: Zadaća 3, Zadatak 3
#include <iostream>
#include <new>
#include <stdexcept>
#include <iomanip>
template <typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata** elementi=nullptr;
    char ime_matrice;
};
template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat)
{
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}
template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona, char ime = 0)
{
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova;
    mat.br_kolona = br_kolona;
    mat.ime_matrice = ime;
    mat.elementi = new TipElemenata*[br_redova] {};
    try {
        for(int i = 0; i < br_redova; i++)
            mat.elementi[i] = new TipElemenata[br_kolona];
    } catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}
template <typename TipElemenata>
void UnesiMatricu(Matrica<TipElemenata> &mat)
{
    for(int i = 0; i < mat.br_redova; i++)
        for(int j = 0; j < mat.br_kolona; j++) {
            std::cout << mat.ime_matrice
                      << "(" << i + 1 << "," << j + 1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}
template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> mat, int sirina_ispisa, int preciznost=6, bool treba_brisati=false)
{
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++)
            std::cout << std::setw(sirina_ispisa)<< std::setprecision(preciznost)<< mat.elementi[i][j];
        std::cout << std::endl;
    }
    if(treba_brisati)
        UnistiMatricu(mat);
}
template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2)
{
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
}
template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2)
{
    if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    auto m3=StvoriMatricu<TipElemenata>(m1.br_redova,m2.br_kolona);
    for(int i=0; i<m1.br_redova; i++) {
        for(int j=0; j<m2.br_kolona; j++) {
            TipElemenata element=0;
            for(int k=0; k<m1.br_kolona; k++)
                element+=m1.elementi[i][k]*m2.elementi[k][j];
            m3.elementi[i][j]=element;
        }
    }
    return m3;
}
template<typename TipElemenata>
Matrica<TipElemenata> PomnozenaSaSkalarom(const Matrica<TipElemenata> &m, double n)
{
    auto mat=StvoriMatricu<TipElemenata>(m.br_redova,m.br_kolona);
    for(int i=0; i<m.br_redova; i++)
        for(int j=0; j<m.br_kolona; j++)
            mat.elementi[i][j]=n*m.elementi[i][j];
    return mat;
}
template <typename TipElemenata>
Matrica<TipElemenata> MatricniHarmonijskiPolinom(const Matrica<TipElemenata> &A, int n)
{
    if(A.br_kolona!=A.br_redova) throw std::domain_error("Matrica nije kvadratna");
    if(n<0) throw std::domain_error ("Pogresan parametar n");
    auto mat=StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona);
    auto stepenovana=StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona);
    auto pomnozenaSaSkalarom=StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona);
    for(int i=0; i<A.br_redova; i++)
        for(int j=0; j<A.br_kolona; j++)
            stepenovana.elementi[i][j]=0;
    for(int i=0; i<A.br_redova; i++)
        stepenovana.elementi[i][i]=1;
    for(int i=0; i<A.br_redova; i++)
        for(int j=0; j<A.br_kolona; j++)
            mat.elementi[i][j]=0;
    for(int k=1; k<=n; k++) {
        auto stepenovanaStepenPrije=stepenovana;
        auto matPrije=mat;
        auto pomnozenaSaSkalaromPrije=pomnozenaSaSkalarom;
        stepenovana=ProduktMatrica(stepenovana,A);
        pomnozenaSaSkalarom=PomnozenaSaSkalarom(stepenovana,1./k);
        mat=ZbirMatrica(mat,pomnozenaSaSkalarom);
        UnistiMatricu(matPrije);
        UnistiMatricu(stepenovanaStepenPrije);
        UnistiMatricu(pomnozenaSaSkalaromPrije);
    }
    UnistiMatricu(stepenovana);
    UnistiMatricu(pomnozenaSaSkalarom);
    return mat;
}
int main()
{
    auto mat=StvoriMatricu<double>(2,2);
    UnesiMatricu(mat);
    IspisiMatricu(MatricniHarmonijskiPolinom(mat,0),10,6,true);
    UnistiMatricu(mat);
    return 0;
}