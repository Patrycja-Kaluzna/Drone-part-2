#ifndef DRON_HH
#define DRON_HH

/*!
 * \file
 * \brief Definicja klasy Dron
 * 
 * Plik zawiera definicję klasy Dron.
 */

#include "prostopadloscian.hh"
#include "wieloscian.hh"
#include <fstream>

/*!
 * \brief Modeluje pojęcie drona,
 * którego cechą jest jego kadłub
 * będący prostopadłościanem.
 */

class Dron {
    
public:

Prostopadloscian _Kadlub;

Wieloscian _Sruba1;

Wieloscian _Sruba2;

void wczytaj (std::string nazwa_pliku1, std::string nazwa_pliku2);

void ruch_na_wprost (double odleglosc);

Wektor3D oblicz_srodek_kadluba (const char uklad) const;

Wektor3D oblicz_srodek_sruby (const int numer_sruby) const;

void zmiana_orientacji_OZ (double kat);

};

#endif