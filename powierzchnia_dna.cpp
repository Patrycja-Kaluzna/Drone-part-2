#include "powierzchnia_dna.hh"



/*!
 * Wczytuje z pliku punkty w 
 * lokalnym układzie odniesienia.
 * \pre Plik powinien zawierać punkty
 *      w lokalnym układzie odniesienia,
 *      które zostaną wczytane.
 */
Powierzchnia_dna::Powierzchnia_dna ()
{
    std::vector<Wektor3D> * pomWsk = zwroc_wskaznik_do_lokalnych();
    std::ifstream Plik;
    Wektor3D pomWek;

    Plik.open("punkty/dno.dat");
    if (Plik.is_open()) 
    {       
        while (Plik >> pomWek) 
        {
            pomWsk->push_back(pomWek);
        }
    } else {
            std::cerr << "Błąd: otwarcie pliku dno.dat nie powiodło się." << std::endl; 
    }
    Plik.close();
}