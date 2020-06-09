#ifndef SCENA_HH
#define SCENA_HH

/*!
 * \file
 * \brief Definicja klasy Scena
 * Plik zawiera definicję klasy Scena.
 */

#include "lacze_do_gnuplota.hh"
#include "powierzchnia_wody.hh"
#include "powierzchnia_dna.hh"
#include "dron.hh"

/*!
 * \brief Modeluje pojęcie sceny, której
 * cechami są jej powierzchnie wody i dna 
 * oraz dron i zbiór przeszkód.
 */

class Scena {    

Powierzchnia_wody _Pwody;

Powierzchnia_dna _Pdna;

std::vector<std::shared_ptr<Odcinek>> _Zbior_przeszkod;

public:

Dron _Dron;

/*!
 * \brief Wczytuje z pliku punkty lokalne
 * i wczytuje punkty globalne przeszkód
 * oraz umieszcza je w kontenerze.
 */
Scena ();

/*!
 * \brief Zapisuje _Punkty_lokalne obiektów _Pwody, 
 * _Pdna oraz _Zbior_przeszkod i _Punkty_globalne 
 * obiektu _Dron do odpowiedniego pliku.
 */
void stworz (std::string nazwa_pliku);

/*!
 * \brief Wykonuje rysunek wcześniej zapisanej w pliku sceny
 * korzystając z programu gnuplot.
 */ 
void rysuj (PzG::LaczeDoGNUPlota Lacze) const;

/*!
 * \brief Sprawdza czy nastąpiła kolizja drona 
 * z przeszkodą.
 */
bool czy_kolizja ();

};

#endif