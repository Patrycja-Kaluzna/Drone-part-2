#ifndef DRON_HH
#define DRON_HH

/*!
 * \file
 * \brief Definicja klasy Dron
 * Plik zawiera definicję klasy Dron.
 */

#include "prostopadloscian.hh"
#include <memory>

/*!
 * \brief Modeluje pojęcie drona,
 * którego cechami są jego kadłub
 * będący prostopadłościanem oraz
 * śruby będące wielościanami.
 */

class Dron {
    
public:

Prostopadloscian _Kadlub;

Wieloscian _Sruba1;

Wieloscian _Sruba2;


/*!
 * \brief Wczytuje z pliku punkty lokalne, 
 * ustawia wartości pól _Wektor_translacji
 * i wczytuje punkty globalne. 
 */
Dron ();

/*!
 * \brief Porusza drona na wprost
 * na zadaną odległość.
 */
void ruch_na_wprost (double odleglosc);

/*!
 * \brief Obraca drona o zadany kąt
 * w wybranym wymiarze.
 */
void zmiana_orientacji (double kat, char wymiar);

/*!
 * \brief Zwraca największą wartość wspołrzędnej x
 * wśród punktów w globalnym układzie odniesienia. 
 */
double zwroc_max_x ();

/*!
 * \brief Zwraca najmniejszą wartość wspołrzędnej x
 * wśród punktów w globalnym układzie odniesienia. 
 */
double zwroc_min_x ();

/*!
 * \brief Zwraca największą wartość wspołrzędnej y
 * wśród punktów w globalnym układzie odniesienia. 
 */
double zwroc_max_y ();

/*!
 * \brief Zwraca najmniejszą wartość wspołrzędnej y
 * wśród punktów w globalnym układzie odniesienia. 
 */
double zwroc_min_y ();

/*!
 * \brief Zwraca największą wartość wspołrzędnej z
 * wśród punktów w globalnym układzie odniesienia. 
 */
double zwroc_max_z ();

/*!
 * \brief Zwraca najmniejszą wartość wspołrzędnej z
 * wśród punktów w globalnym układzie odniesienia. 
 */
double zwroc_min_z ();

/*!
 * \brief Sprawdza czy nastąpiła kolizja drona 
 * z przeszkodą.
 */
bool czy_kolizja (std::vector<std::shared_ptr<Odcinek>> zbior_przeszkod);

};

#endif