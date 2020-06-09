#include "powierzchnia_wody.hh"



/*!
 * Wczytuje z pliku punkty w 
 * lokalnym układzie odniesienia.
 * \pre Plik powinien zawierać punkty
 *      w lokalnym układzie odniesienia,
 *      które zostaną wczytane.
 */
Powierzchnia_wody::Powierzchnia_wody ()
{
    std::vector<Wektor3D> * pomWsk = zwroc_wskaznik_do_lokalnych();
    std::ifstream Plik;
    Wektor3D pomWek;

    Plik.open("punkty/woda.dat");
    if (Plik.is_open()) 
    {       
        while (Plik >> pomWek) 
        {
            pomWsk->push_back(pomWek);
        }
    } else {
            std::cerr << "Błąd: otwarcie pliku woda.dat nie powiodło się." << std::endl; 
    }
    Plik.close();
}