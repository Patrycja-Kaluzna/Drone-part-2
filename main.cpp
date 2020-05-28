#include <iostream>
#include <vector>
#include <cmath>

class FiguraGeometryczna {

public:

virtual double obliczPolePowierzchni() const
{
    return 0;
}

virtual std::string zwrocNazwe() const
{
    return "figura geometryczna";
}

};

class Kolo: public FiguraGeometryczna {

public:

double dlugoscPromienia;

virtual double obliczPolePowierzchni() const override
{
    return M_PI * dlugoscPromienia * dlugoscPromienia;
}

virtual std::string zwrocNazwe() const override
{
    return "kolo";
}

};

class Prostokat: public FiguraGeometryczna {

public:

double dlugoscBokuA;

double dlugoscBokuB;

virtual double obliczPolePowierzchni() const override
{
    return dlugoscBokuA * dlugoscBokuB;
}

virtual std::string zwrocNazwe() const override
{
    return "prostokat";
}

};

using namespace std;

int main()
{
    vector<FiguraGeometryczna> wektorFigur;
    vector<FiguraGeometryczna>::iterator I;
    Kolo kolo1, kolo2;
    Prostokat prostokat1, prostokat2;

    kolo1.dlugoscPromienia = 1;
    kolo2.dlugoscPromienia = 2;
    prostokat1.dlugoscBokuA = 1;
    prostokat1.dlugoscBokuB = 2;
    prostokat2.dlugoscBokuA = 3;
    prostokat2.dlugoscBokuB = 4;

    wektorFigur.push_back(kolo1);
    wektorFigur.push_back(kolo2);
    wektorFigur.push_back(prostokat1);
    wektorFigur.push_back(prostokat2);

    for (I = wektorFigur.begin(); I != wektorFigur.end(); ++I)
    {
        cout << "Figury geometryczna jest typu: " << (*I).zwrocNazwe();
        cout << ". Jej pole powierzchni rowna sie: " << (*I).obliczPolePowierzchni();
        cout << endl;
    }
}