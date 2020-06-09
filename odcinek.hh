#ifndef ODCINEK_HH
#define ODCINEK_HH

/*!
 * \file
 * \brief Definicja klasy Odcinek.
 * Plik zawiera definicję klasy 
 * Odcinek, która jest klasą bazową.
 */ 

#include "SWektor.hh"
#include <fstream>
#include <vector>

/*!
 * \brief Modeluje pojęcie odcinka,
 * którego cechami są zbiory jego
 * punktów w lokalnym i globalnym 
 * układzie odniesienia.
 */

typedef SWektor<double, 3> Wektor3D;

class Odcinek {

protected:

std::vector<Wektor3D> _Punkty_lokalne;

std::vector<Wektor3D> _Punkty_globalne;

public:

/*!
 * \brief Umożliwia czytanie punktów 
 * w lokalnym układzie odniesienia.
 */
std::vector<Wektor3D>::const_iterator get_Punkty_lokalne () const;

/*!
 * \brief Umożliwia wczytywanie punktów 
 * w lokalnym układzie odniesienia.
 */
std::vector<Wektor3D>::iterator set_Punkty_lokalne ();

/*!
 * \brief Pozwala na dostęp do punktów 
 * w lokalnym układzie odniesienia.
 */
std::vector<Wektor3D> * zwroc_wskaznik_do_lokalnych ();

/*!
 * \brief Pozwala na dostęp do punktów 
 * w globalnym układzie odniesienia.
 */
std::vector<Wektor3D> * zwroc_wskaznik_do_globalnych ();

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

};

/*!
 * \brief Wczytuje zbiór punktów w lokalnym układzie odniesienia
 * ze strumienia plikowego.
 */ 
std::ifstream & operator >> (std::ifstream & Fstr, Odcinek & Pow);

/*!
 * \brief Zapisuje zbiór punktów w lokalnym układzie odniesienia
 * na strumieniu plikowym.
 */ 
std::ofstream & operator << (std::ofstream & Fstr, Odcinek & Odc);

#endif