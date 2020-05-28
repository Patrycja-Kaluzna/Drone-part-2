#include "scena.hh"



/*!
 * Inicjalizuje pola _Punkty_lokalne obiektów _Pwody i _Pdna.
 */ 
Scena::Scena ()
{
    std::vector<Wektor3D> * lokalne_wody = _Pwody.get_Punkty_lokalne();
    std::vector<Wektor3D> * lokalne_dna = _Pdna.get_Punkty_lokalne();
    std::ifstream plik;
    Wektor3D pomWek;

    plik.open("plaszczyzny/woda.dat", std::ios::in);
    if (plik.is_open())
    {       
        while (plik >> pomWek)
        {
            lokalne_wody->push_back(pomWek);
        }
    } else {
            std::cerr << "Błąd: otwarcie pliku woda.dat nie powiodło się." << std::endl; 
    }
    plik.close();

    plik.open("plaszczyzny/dno.dat", std::ios::in);
    if (plik.is_open())
    {       
        while (plik >> pomWek)
        {
            lokalne_dna->push_back(pomWek);
        }
    } else {
            std::cerr << "Błąd: otwarcie pliku dna.dat nie powiodło się." << std::endl; 
    }
    plik.close();
}



/*!
 * Zapisuje _Punkty_lokalne obiektów _Pwody i _Pdna oraz 
 * _Punkty_globalne obiektu _Dron do odpowiedniego pliku.
 * \param[in] nazwa_pliku - nazwa pliku, do którego
 *              zostaną zapisane dane.
 */ 
void Scena::stworz (std::string nazwa_pliku)
{
    std::vector<Wektor3D> * lokalne_wody = _Pwody.get_Punkty_lokalne();
    std::vector<Wektor3D> * lokalne_dna = _Pdna.get_Punkty_lokalne();
    std::vector<Wektor3D>::const_iterator globalne_kadlub = _Dron._Kadlub.get_Punkty_globalne();
    std::vector<Wektor3D>::const_iterator globalne_sruba1 = _Dron._Sruba1.get_Punkty_globalne();
    std::vector<Wektor3D>::const_iterator globalne_sruba2 = _Dron._Sruba2.get_Punkty_globalne();
    unsigned int liczba_globalynch_kadlub = _Dron._Kadlub.liczba_Punktow_globalnych();
    unsigned int liczba_globalynch_sruby = _Dron._Sruba1.liczba_Punktow_globalnych();
    std::ofstream plik;
    unsigned int i;

    plik.open(nazwa_pliku);
    if (plik.is_open())
    {
        plik << "# DRON \n";
        for (i = 0; i < liczba_globalynch_kadlub; ++i)
        {
            plik << *globalne_kadlub << '\n';
            ++globalne_kadlub;
        }
        plik << "\n # \n";
        for (i = 0; i < liczba_globalynch_sruby; ++i)
        {
            plik << *globalne_sruba1 << '\n';
            ++globalne_sruba1;
        }
        plik << "\n # \n";
        for (i = 0; i < liczba_globalynch_sruby; ++i)
        {
            plik << *globalne_sruba2 << '\n';
            ++globalne_sruba2;
        }
        plik << "\n # POWIERZCHNIA WODY \n";
        for (i = 0; i < lokalne_wody->size(); ++i)
        {
            plik << (*lokalne_wody)[i] << '\n';
        }
        plik << "\n # POWIERZCHNIA DNA \n";
        for (i = 0; i < lokalne_dna->size(); ++i)
        {
            plik << (*lokalne_dna)[i] << '\n';
        }
    } else {
        std::cerr << "Błąd: otwarcie pliku " << nazwa_pliku << " nie powiodło się." << std::endl;
    }
    plik.close();
}



/*!
 * Wykonuje rysunek wcześniej zapisanej sceny w
 * korzystając z programu gnuplot.
 * \param[in] Lacze - łącze do programu gnuplot.
 */ 
void Scena::rysuj (PzG::LaczeDoGNUPlota Lacze) const
{
    Lacze.Rysuj();
}