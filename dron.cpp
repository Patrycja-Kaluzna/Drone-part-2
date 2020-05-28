#include "dron.hh"

void Dron::wczytaj (std::string nazwa_pliku1, std::string nazwa_pliku2)
{
    std::ifstream Punkty_lokalne;

    Punkty_lokalne.open(nazwa_pliku1);
    if (Punkty_lokalne.is_open())
    {
        Punkty_lokalne >> _Kadlub;
    } else {
        std::cerr << "Błąd: otwarcie pliku " << nazwa_pliku1 << " nie powiodło się." << std::endl; 
    }
    Punkty_lokalne.close();

    Punkty_lokalne.open(nazwa_pliku2);
    if (Punkty_lokalne.is_open())
    {
        Punkty_lokalne >> _Sruba1;
    } else {
        std::cerr << "Błąd: otwarcie pliku " << nazwa_pliku2 << " nie powiodło się." << std::endl; 
    }
    Punkty_lokalne.close();

    Punkty_lokalne.open(nazwa_pliku2);
    if (Punkty_lokalne.is_open())
    {
        Punkty_lokalne >> _Sruba2;
    } else {
        std::cerr << "Błąd: otwarcie pliku " << nazwa_pliku2 << " nie powiodło się." << std::endl; 
    }
    Punkty_lokalne.close();

    _Kadlub._Wektor_translacji[0] = 10; _Kadlub._Wektor_translacji[1] = 10; _Kadlub._Wektor_translacji[2] = 25;
    _Sruba1._Wektor_translacji[0] = 0; _Sruba1._Wektor_translacji[1] = -15; _Sruba1._Wektor_translacji[2] = 40;
    _Sruba2._Wektor_translacji[0] = 20; _Sruba2._Wektor_translacji[1] = -15; _Sruba2._Wektor_translacji[2] = 40;

    _Kadlub.wczytaj_globalne();
    _Sruba1.wczytaj_globalne();
    _Sruba2.wczytaj_globalne();
}



void Dron::ruch_na_wprost (double odleglosc)
{
    _Kadlub.ruch_na_wprost(odleglosc);
    _Sruba1.ruch_na_wprost(odleglosc);
    _Sruba2.ruch_na_wprost(odleglosc);
}



Wektor3D Dron::oblicz_srodek_kadluba (const char uklad) const
{
    Wektor3D pomWek;
    pomWek[0] = 0; pomWek[1] = 0; pomWek[2] = 0;
    unsigned int i;

    if (uklad == 'l')
    {
        std::vector<Wektor3D>::const_iterator I = _Kadlub.wez_Punkty_lokalne();
        for (i = 0; i < 8; ++i)
        {
            if (i != 4)
            {
                pomWek = pomWek + *I;
            }
            ++I;
        }
    }
    if (uklad == 'g')
    {
        std::vector<Wektor3D>::const_iterator I = _Kadlub.get_Punkty_globalne();
        for (i = 0; i < 8; ++i)
        {
            if (i != 4)
            {
                pomWek = pomWek + *I;
            }
            ++I;
        }    
    }    

    return pomWek;
}



Wektor3D Dron::oblicz_srodek_sruby (const int numer_sruby) const
{
    Wektor3D pomWek;
    pomWek[0] = 0; pomWek[1] = 0; pomWek[2] = 0;
    unsigned int i;

    if (numer_sruby == 1)
    {
        std::vector<Wektor3D>::const_iterator I = _Sruba1.get_Punkty_globalne();
        for (i = 0; i < 27; ++i)
        {
            if (i != 4 && i != 7 && i != 8 && i != 11 && i != 12 && i != 15 && i != 16 && i != 19 && i != 20 &&
            i != 23 && i != 24)
            {
                pomWek = pomWek + *I;
            }
            ++I;
        }
        pomWek = pomWek / 27;
    }
    if (numer_sruby == 2)
    {
        std::vector<Wektor3D>::const_iterator I = _Sruba2.get_Punkty_globalne();
        for (i = 0; i < 27; ++i)
        {
            if (i != 4 && i != 7 && i != 8 && i != 11 && i != 12 && i != 15 && i != 16 && i != 19 && i != 20 &&
            i != 23 && i != 24)
            {
                pomWek = pomWek + *I;
            }
            ++I;
        }
        pomWek = pomWek / 27;
    }
    return pomWek;
}



void Dron::zmiana_orientacji_OZ (double kat)
{
    unsigned int i, liczba_globalnych_sruby = _Sruba1.liczba_Punktow_globalnych();
    std::vector<Wektor3D>::iterator I1 = _Sruba1.set_Punkty_globalne();
    std::vector<Wektor3D>::iterator I3 = _Sruba1.set_Punkty_lokalne();
    std::vector<Wektor3D>::iterator I2 = _Sruba2.set_Punkty_globalne();
    std::vector<Wektor3D>::iterator I4 = _Sruba2.set_Punkty_lokalne();
    Wektor3D pomWek1, pomWek2;
    
    pomWek1[0] = -10; pomWek1[1] = -25; pomWek1[2] = 15;
    pomWek2[0] = 10; pomWek2[1] = -25; pomWek2[2] = 15;

    _Kadlub.zmiana_orientacji_OZ(kat);
    for (i = 0; i < liczba_globalnych_sruby; ++i)
    {
        *I1 = _Kadlub._Macierz_rotacji * (*I3 + pomWek1) - pomWek1 + _Sruba1._Wektor_translacji;
        *I2 = _Kadlub._Macierz_rotacji * (*I4 + pomWek2) - pomWek2 + _Sruba2._Wektor_translacji;
        ++I1; ++I2; ++I3; ++I4;  
    }
}