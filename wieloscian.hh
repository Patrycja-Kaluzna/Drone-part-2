#ifndef WIELOSCIAN_HH
#define WIELOSCIAN_HH

/*!
 * \file
 * \brief Definicja klasy Wieloscian.
 * Plik zawiera definicję klasy Wieloscian,
 * która jest klasą pochodną klasy Powierzchnia.
 */

#include "powierzchnia.hh"
#include "SMacierz.hh"
#include <cmath>

/*!
 * \brief Modeluje pojęcie wielościanu,
 * którego cechami są zbiory jego punktów
 * w lokalnym oraz globalnym układzie
 * odniesienia, a także wektor translacji
 * i macierz rotacji oraz kąty orientacji 
 * w wymiarach X, Y i Z.
 */

typedef SMacierz <double, 3> Macierz3x3;
                         
class Wieloscian: public Powierzchnia {

double _Kat_orientacjiX;

double _Kat_orientacjiY;

double _Kat_orientacjiZ;

char _ostatnia_zmiana_orientacji;

public:

Macierz3x3 _Macierz_rotacji;

Wektor3D _Wektor_translacji;

/*!
 * \brief Ustawia wartości pól _Kat_orientacjiX, _Kat_orientacjiY
 * i _Kat_orientacjiZ na 0, _Macierz_rotacji jako macierz obrotu 
 * wokół osi Z oraz _ostatnia_zmiana_orientacji na z. 
 */
Wieloscian ();

/*!
 * \brief Wczytuje zbiór punktów w
 * globalnym układzie odniesienia.
 */
void wczytaj_globalne ();

/*!
 * \brief Umożliwia czytanie punktów 
 * w globalnym układzie odniesienia.
 */
std::vector<Wektor3D>::const_iterator get_Punkty_globalne () const;

/*!
 * \brief Umożliwia wczytywanie punktów 
 * w globalnym układzie odniesienia.
 */
std::vector<Wektor3D>::iterator set_Punkty_globalne ();

/*!
 * \brief Zwraca liczbę elementów kontenera
 * z punktami w globalnym układzie odniesienia.
 */
unsigned int liczba_Punktow_globalnych () const;

/*!
 * \brief Ustawia wartość pola _Kat_orientacji
 * odpowiednio X, Y lub Z.
 */
void ustaw_Kat_orientacji (double kat, char wymiar);

/*!
 * \brief Oblicza macierz obrotu wokół
 * osi odpowiednio X, Y lub Z.
 */
Macierz3x3 oblicz_Macierz_rotacji (char wymiar) const;

/*!
 * \brief Ustawia wartość pola _Macierz_rotacji
 * jako macierz obrotu wokół osi odpowiednio X,
 * Y lub Z.
 */
void ustaw_Macierz_rotacji (char wymiar);

/*!
 * \brief Oblicza wektor przemieszczenia
 * na zadaną odległość.
 */
Wektor3D oblicz_Wektor_przemieszczenia (double odleglosc) const;

/*!
 * \brief Uaktualnia wartość pola 
 * _Wektor_translacji o zadaną odległość.
 */
void ustaw_Wektor_translacji (double odleglosc);

/*!
 * \brief Obraca wielościan o zadany kąt
 * w wybranym wymiarze.
 */
void zmiana_orientacji (double kat, char wymiar);

/*!
 * \brief Porusza wielościan na wprost
 * na zadaną odległość.
 */
void ruch_na_wprost (double odleglosc);

};

#endif