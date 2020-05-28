#include "lacze_do_gnuplota.hh"
#include "scena.hh"

#include <iostream>
#include <unistd.h>
#include <iomanip>

using namespace std;

/*!
 * \brief Wyświetla menu opcji.
 */ 
void wyswietl_menu ()
{
    cout << "Dostępne opcje:" << endl;
    cout << "m - powróć do menu opcji" << endl << "r - zadaj ruch na wprost" << endl;
    cout << "o - zadaj zmianę orientacji" << endl << "k - zakończ działanie programu" << endl;
}

/*!
 * \brief Wyświetla aktualną i łączną ilość obiektów klasy SWektor<double, 3>. 
 */ 
void wyswietl_ilosc_Wektorow3D ()
{
    cout << "Aktualna ilość obiektów Wektor3D: " << Wektor3D::get_aktualna_ilosc() << endl;
    cout << "Łączna ilość obiektów Wektor3D: " << Wektor3D::get_laczna_ilosc() << endl;
}

int main ()
{
    string nazwa_pliku_pglobalne = "plaszczyzny/dron2.dat";
    string nazwa_pliku_kadlub = "plaszczyzny/dron1.dat";
    string nazwa_pliku_scena = "plaszczyzny/scena.dat";
    string nazwa_pliku_sruby = "plaszczyzny/graniastoslup-osY.dat";
    ofstream Punkty_globalne;
    ifstream Punkty_lokalne;
    Scena Scena;
    PzG::LaczeDoGNUPlota Lacze;
    unsigned int i;
    char opcja;    
   
    Scena._Dron.wczytaj(nazwa_pliku_kadlub, nazwa_pliku_sruby);
    Scena.stworz(nazwa_pliku_scena);

    Lacze.UsunWszystkieNazwyPlikow();
    Lacze.DodajNazwePliku("plaszczyzny/scena.dat");
    //Lacze.DodajNazwePliku("plaszczyzny/test.dat");

    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj();
    Lacze.UstawZakresX(-100, 100);
    Lacze.UstawZakresY(-100, 100);
    Lacze.UstawZakresZ(0, 150);
    Lacze.UstawRotacjeXZ(40, 60);

    Scena.rysuj(Lacze);

    wyswietl_menu();
    wyswietl_ilosc_Wektorow3D();

    do {
        cin >> opcja;
        switch (opcja)
        {
            case 'm':
            {
                wyswietl_menu();
                wyswietl_ilosc_Wektorow3D();
                break;
            }
            case 'r':
            {
                double odleglosc;
                cout << "Podaj odległość, na którą ma przemieścić się dron: ";
                cin >> odleglosc;
                for (i = 0; i < 5; ++i)
                {
                    Scena._Dron.ruch_na_wprost(odleglosc / 5);
                    Scena.stworz(nazwa_pliku_scena);
                    Scena.rysuj(Lacze);
                    usleep(50000);
                }
                wyswietl_ilosc_Wektorow3D();
                break;
            }
            case 'o':
            {
                double kat;
                cout << "Podaj kąt, o który ma obrócić się dron (w stopniach): ";
                cin >> kat;
                for (i = 0; i < 5; ++i)
                {
                    Scena._Dron.zmiana_orientacji_OZ(kat / 5);
                    Scena.stworz(nazwa_pliku_scena);
                    Scena.rysuj(Lacze);
                    usleep(50000);
                }
                wyswietl_ilosc_Wektorow3D();
                break;
            }
            case 'k':
            {
                cout << "Koniec działania programu" << endl;
                wyswietl_ilosc_Wektorow3D();
                break;
            }
            default:
            {
                cout << "Bład: niepoprawna opcja. Wybierz opcje jeszcze raz." << endl;
                break;
            }
        }
    } while (opcja != 'k');

    Lacze.UsunWszystkieNazwyPlikow();
}