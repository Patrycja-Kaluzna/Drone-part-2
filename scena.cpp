#include "scena.hh"



/*!
 * Wczytuje z pliku punkty lokalne
 * i wczytuje punkty globalne przeszkód
 * oraz umieszcza je w kontenerze.
 * \pre Pliki powinny zawierać punkty
 *      w lokalnym układzie odniesienia,
 *      które zostaną wczytane.
 */
Scena::Scena ()
{
    Odcinek Odc;
    Powierzchnia Pow;
    Prostopadloscian Pro;
    std::vector<Wektor3D> * pomWsk1 = Odc.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * pomWsk2 = Pow.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * pomWsk3 = Odc.zwroc_wskaznik_do_lokalnych();
    std::vector<Wektor3D> * pomWsk4 = Pow.zwroc_wskaznik_do_lokalnych();
    std::ifstream Plik;
    unsigned int i;

    Plik.open("punkty/przeszkoda-pret.dat");
    if (Plik.is_open()) {
        Plik >> Odc;
    } else {
        std::cerr << "Błąd: otwarcie pliku przeszkoda-pret.dat nie powiodło się." << std::endl; 
    }
    Plik.close();
    Plik.open("punkty/przeszkoda-powierzchnia.dat");
    if (Plik.is_open()) {
        Plik >> Pow;
    } else {
        std::cerr << "Błąd: otwarcie pliku przeszkoda-powierzchnia.dat nie powiodło się." << std::endl; 
    }
    Plik.close();
    Plik.open("punkty/przeszkoda-prostopadloscian.dat");
    if (Plik.is_open()) {
        Plik >> Pro;
    } else {
        std::cerr << "Błąd: otwarcie pliku przeszkoda-prostopadloscian.dat nie powiodło się." << std::endl; 
    }
    Plik.close();

    for (i = 0; i < pomWsk3->size(); ++i)
    {
        pomWsk1->push_back(pomWsk3->at(i));    
    }
    for (i = 0; i < pomWsk4->size(); ++i)
    {
        pomWsk2->push_back(pomWsk4->at(i));    
    }
    Pro.wczytaj_globalne();

    _Zbior_przeszkod.push_back(std::make_shared<Odcinek>(Odc));
    _Zbior_przeszkod.push_back(std::make_shared<Odcinek>(Pow));
    _Zbior_przeszkod.push_back(std::make_shared<Odcinek>(Pro));
}



/*!
 * Zapisuje _Punkty_lokalne obiektów _Pwody, _Pdna 
 * oraz _Zbior_przeszkod i _Punkty_globalne 
 * obiektu _Dron do odpowiedniego pliku.
 * \param [in] nazwa_pliku - nazwa pliku, do którego
 *        zostaną zapisane dane.
 */ 
void Scena::stworz (std::string nazwa_pliku)
{   
    std::vector<Wektor3D>::const_iterator globalne_kadluba = _Dron._Kadlub.get_Punkty_globalne();
    std::vector<Wektor3D>::const_iterator globalne_sruby1 = _Dron._Sruba1.get_Punkty_globalne();
    std::vector<Wektor3D>::const_iterator globalne_sruby2 = _Dron._Sruba2.get_Punkty_globalne();
    unsigned int liczba_globalynch_kadluba = _Dron._Kadlub.liczba_Punktow_globalnych();
    unsigned int liczba_globalynch_sruby = _Dron._Sruba1.liczba_Punktow_globalnych();
    std::vector<Wektor3D> * lokalne_wody = _Pwody.zwroc_wskaznik_do_lokalnych();
    std::vector<Wektor3D> * lokalne_dna = _Pdna.zwroc_wskaznik_do_lokalnych();
    std::ofstream Plik;
    unsigned int i;

    Plik.open(nazwa_pliku);
    if (Plik.is_open())
    {
        Plik << "#DRON \n";
        for (i = 0; i < liczba_globalynch_kadluba; ++i)
        {
            Plik << *globalne_kadluba << '\n';
            ++globalne_kadluba;
        }
        Plik << "\n# \n";
        for (i = 0; i < liczba_globalynch_sruby; ++i)
        {
            Plik << *globalne_sruby1 << '\n';
            ++globalne_sruby1;
        }
        Plik << "\n# \n";
        for (i = 0; i < liczba_globalynch_sruby; ++i)
        {
            Plik << *globalne_sruby2 << '\n';
            ++globalne_sruby2;
        }
        Plik << "\n#POWIERZCHNIA WODY \n";
        for (i = 0; i < lokalne_wody->size(); ++i)
        {
            Plik << (*lokalne_wody)[i] << '\n';
        }
        Plik << "\n#POWIERZCHNIA DNA \n";
        for (i = 0; i < lokalne_dna->size(); ++i)
        {
            Plik << (*lokalne_dna)[i] << '\n';
        }
        Plik << "\n#PRZESZKODY \n";
        for (i = 0; i < _Zbior_przeszkod.size(); ++i)
        {
            if (i != (_Zbior_przeszkod.size() - 1))
            {
                Plik << *(_Zbior_przeszkod.at(i)) << "\n\n#\n";
            } else {
                Plik << *(_Zbior_przeszkod.at(i));
            }
        }
    } else {
        std::cerr << "Błąd: otwarcie pliku " << nazwa_pliku << " nie powiodło się." << std::endl;
    }
    Plik.close();
}



/*!
 * Wykonuje rysunek wcześniej zapisanej w plku 
 * sceny korzystając z programu gnuplot.
 * \param [in] Lacze - łącze do programu gnuplot.
 */ 
void Scena::rysuj (PzG::LaczeDoGNUPlota Lacze) const
{
    Lacze.Rysuj();
}



/*!
 * Sprawdza czy nastąpiła kolizja drona z przeszkodą.
 * \return Zwraca true jeśli nastąpiła kolizja z
 *         którąkolwiek przeszkodą, a false 
 *         jeśli nie nastąpiła z żadną.
 */
bool Scena::czy_kolizja ()
{
    if (_Dron.czy_kolizja(_Zbior_przeszkod))
    {
        return true;
    } else {
        return false;
    }
}