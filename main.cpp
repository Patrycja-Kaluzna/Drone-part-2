#include "scena.hh"

#include <iostream>
#include <unistd.h>

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
    { 
        string nazwa_pliku_sceny = "punkty/scena.dat";
        PzG::LaczeDoGNUPlota Lacze;
        double odleglosc, kat;
        char opcja, wymiar;
        unsigned int i;
        Scena Scena;
   
        Scena.stworz(nazwa_pliku_sceny);

        Lacze.UsunWszystkieNazwyPlikow();
        Lacze.DodajNazwePliku("punkty/scena.dat");

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
                    cout << "Podaj odległość, na którą ma przemieścić się dron: ";
                    cin >> odleglosc;
                    for (i = 0; i < 5; ++i)
                    {
                        Scena._Dron.ruch_na_wprost(odleglosc / 5);
                        if (Scena.czy_kolizja())
                        {
                            cout << endl << "Ruch przerwany - nastąpiłaby kolizja drona z przeszkodą." << endl << endl;
                            Scena._Dron.ruch_na_wprost(-odleglosc / 5);
                            break;
                        } else {
                            Scena.stworz(nazwa_pliku_sceny);
                            Scena.rysuj(Lacze);
                            usleep(50000);
                        }
                    }
                    wyswietl_ilosc_Wektorow3D();
                    break;
                }
                case 'o':
                {
                    cout << "Podaj kąt, o który ma obrócić się dron (w stopniach): ";
                    cin >> kat;
                    cout << "Podaj literę odpowiadającą osi, wokół której ma obrócić się dron (x, y lub z): ";
                    cin >> wymiar;
                    for (i = 0; i < 5; ++i)
                    {
                        Scena._Dron.zmiana_orientacji((kat / 5), wymiar);
                        if (Scena.czy_kolizja())
                        {
                            cout << endl << "Ruch przerwany - nastąpiłaby kolizja drona z przeszkodą." << endl << endl;
                            Scena._Dron.zmiana_orientacji((-kat / 5), wymiar);
                            break;
                        } else {
                            Scena.stworz(nazwa_pliku_sceny);
                            Scena.rysuj(Lacze);
                            usleep(50000);
                        }
                    }
                    wyswietl_ilosc_Wektorow3D();
                    break;
                }
                case 'k':
                {
                    cout << "Koniec działania programu" << endl;
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
    wyswietl_ilosc_Wektorow3D();
}