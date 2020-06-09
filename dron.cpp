#include "dron.hh"



/*!
 * Wczytuje z pliku punkty w lokalnym
 * układzie odniesienia, ustawia wartości
 * pół _Wektor_translacji i wczytuje punkty
 * w globalnym układzie odniesienia.
 * \pre Pliki powinny zawierać punkty
 *      w lokalnym układzie odniesienia,
 *      które zostaną wczytane.
 */
Dron::Dron ()
{
    std::ifstream Plik;

    Plik.open("punkty/kadlub.dat");
    if (Plik.is_open()) {
        Plik >> _Kadlub;
    } else {
        std::cerr << "Błąd: otwarcie pliku kadlub.dat nie powiodło się." << std::endl; 
    }
    Plik.close();
    Plik.open("punkty/sruby.dat");
    if (Plik.is_open()) {
        Plik >> _Sruba1;
    } else {
        std::cerr << "Błąd: otwarcie pliku sruby.dat nie powiodło się." << std::endl; 
    }
    Plik.close();
    Plik.open("punkty/sruby.dat");
    if (Plik.is_open()) {
        Plik >> _Sruba2;
    } else {
        std::cerr << "Błąd: otwarcie pliku sruby.dat nie powiodło się." << std::endl; 
    }
    Plik.close();

    _Kadlub._Wektor_translacji[0] = 10;
    _Kadlub._Wektor_translacji[1] = 10;
    _Kadlub._Wektor_translacji[2] = 25;
    _Sruba1._Wektor_translacji[0] = 0;
    _Sruba1._Wektor_translacji[1] = -15;
    _Sruba1._Wektor_translacji[2] = 40;
    _Sruba2._Wektor_translacji[0] = 20;
    _Sruba2._Wektor_translacji[1] = -15; 
    _Sruba2._Wektor_translacji[2] = 40;

    _Kadlub.wczytaj_globalne();
    _Sruba1.wczytaj_globalne();
    _Sruba2.wczytaj_globalne();
}



/*!
 * Porusza drona na wprost na zadaną odległość.
 * \param [in] odleglosc - odległość, na którą
 *        ma poruszyć się dron.
 */
void Dron::ruch_na_wprost (double odleglosc)
{
    _Kadlub.ruch_na_wprost(odleglosc);
    _Sruba1.ruch_na_wprost(odleglosc);
    _Sruba2.ruch_na_wprost(odleglosc);
}



/*!
 * Obraca drona o zadany kąt w wybranym wymiarze.
 * \param [in] kat - kąt, o który ma 
 *        obrócic się dron.
 * \param [in] wymiar - wymiar, w którym ma 
 *        obrócić się dron.
 */
void Dron::zmiana_orientacji (double kat, char wymiar)
{
    unsigned int i, liczba_globalnych_sruby = _Sruba1.liczba_Punktow_globalnych();
    std::vector<Wektor3D>::iterator I1 = _Sruba1.set_Punkty_globalne();
    std::vector<Wektor3D>::iterator I3 = _Sruba1.set_Punkty_lokalne();
    std::vector<Wektor3D>::iterator I2 = _Sruba2.set_Punkty_globalne();
    std::vector<Wektor3D>::iterator I4 = _Sruba2.set_Punkty_lokalne();
    Wektor3D pomWek1, pomWek2;
    
    pomWek1[0] = -10;
    pomWek1[1] = -25; 
    pomWek1[2] = 15;
    pomWek2[0] = 10; 
    pomWek2[1] = -25; 
    pomWek2[2] = 15;

    _Kadlub.zmiana_orientacji(kat, wymiar);
    for (i = 0; i < liczba_globalnych_sruby; ++i)
    {
        *I1 = _Kadlub._Macierz_rotacji * (*I3 + pomWek1) + _Kadlub._Macierz_rotacji * (_Sruba1._Wektor_translacji - pomWek1);
        *I2 = _Kadlub._Macierz_rotacji * (*I4 + pomWek2) + _Kadlub._Macierz_rotacji * (_Sruba2._Wektor_translacji - pomWek2);
        ++I1; ++I2; ++I3; ++I4;  
    }
}



/*!
 * Zwraca największą wartość 
 * wspołrzędnej x wśród punktów 
 * w globalnym układzie odniesienia
 * zarówno kadłuba i śrub.
 * \pre Kontenery przechowujące zbiory
 *      puntków w globalnym układzie
 *      odniesienia muszą zawierać dane.
 * \return Zwraca największą wartość 
 *         wspołrzędnej x wśród punktów 
 *         w globalnym układzie odniesienia
 *         zarówno kadłuba i śrub.  
 */
double Dron::zwroc_max_x () {
    std::vector<Wektor3D> * Kadlub_globalne = _Kadlub.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba1_globalne = _Sruba1.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba2_globalne = _Sruba2.zwroc_wskaznik_do_globalnych();
    double max_x = (*Kadlub_globalne).at(0)[0];
    double pom1 = (*Sruba1_globalne).at(0)[0];
    double pom2 = (*Sruba2_globalne).at(0)[0];
    unsigned int i;

    for (i = 1; i < (*Kadlub_globalne).size(); ++i) {
        if (max_x < (*Kadlub_globalne).at(i)[0]){
            max_x = (*Kadlub_globalne).at(i)[0];
        }
    }
    for (i = 1; i < (*Sruba1_globalne).size(); ++i) {
        if (pom1 < (*Sruba1_globalne).at(i)[0]) {
            pom1 = (*Sruba1_globalne).at(i)[0];
        }
    }
    for (i = 1; i < (*Sruba2_globalne).size(); ++i) {
        if (pom2 < (*Sruba2_globalne).at(i)[0]) {
            pom2 = (*Sruba2_globalne).at(i)[0];
        }
    }
    if (max_x > pom1) {
        if (max_x > pom2) {
            return max_x;
        } else {
            return pom2;
        }
    } else {
        if (pom1 > pom2) {
            return pom1;
        } else {
            return pom2;
        }
    }
    return max_x;
}



/*!
 * Zwraca najmniejszą wartość 
 * wspołrzędnej x wśród punktów 
 * w globalnym układzie odniesienia
 * zarówno kadłuba i śrub.
 * \pre Kontenery przechowujące zbiory
 *      puntków w globalnym układzie
 *      odniesienia muszą zawierać dane.
 * \return Zwraca najmniejszą wartość 
 *         wspołrzędnej x wśród punktów 
 *         w globalnym układzie odniesienia
 *         zarówno kadłuba i śrub.  
 */
double Dron::zwroc_min_x () {
    std::vector<Wektor3D> * Kadlub_globalne = _Kadlub.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba1_globalne = _Sruba1.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba2_globalne = _Sruba2.zwroc_wskaznik_do_globalnych();
    double min_x = (*Kadlub_globalne).at(0)[0];
    double pom1 = (*Sruba1_globalne).at(0)[0];
    double pom2 = (*Sruba2_globalne).at(0)[0];
    unsigned int i;

    for (i = 1; i < (*Kadlub_globalne).size(); ++i) {
        if (min_x > (*Kadlub_globalne).at(i)[0]) {
            min_x = (*Kadlub_globalne).at(i)[0];
        }
    }
    for (i = 1; i < (*Sruba1_globalne).size(); ++i) {
        if (pom1 > (*Sruba1_globalne).at(i)[0]) {
            pom1 = (*Sruba1_globalne).at(i)[0];
        }
    }
    for (i = 1; i < (*Sruba2_globalne).size(); ++i) {
        if (pom2 > (*Sruba2_globalne).at(i)[0]) {
            pom2 = (*Sruba2_globalne).at(i)[0];
        }
    }
    if (min_x < pom1) {
        if (min_x < pom2) {
            return min_x;
        } else {
            return pom2;
        }
    } else {
        if (pom1 < pom2) {
            return pom1;
        } else {
            return pom2;
        }
    }
    return min_x;
}



/*!
 * Zwraca największą wartość 
 * wspołrzędnej y wśród punktów 
 * w globalnym układzie odniesienia
 * zarówno kadłuba i śrub.
 * \pre Kontenery przechowujące zbiory
 *      puntków w globalnym układzie
 *      odniesienia muszą zawierać dane.
 * \return Zwraca największą wartość 
 *         wspołrzędnej y wśród punktów 
 *         w globalnym układzie odniesienia
 *         zarówno kadłuba i śrub.  
 */
double Dron::zwroc_max_y () {
    std::vector<Wektor3D> * Kadlub_globalne = _Kadlub.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba1_globalne = _Sruba1.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba2_globalne = _Sruba2.zwroc_wskaznik_do_globalnych();
    double max_y = (*Kadlub_globalne).at(0)[1];
    double pom1 = (*Sruba1_globalne).at(0)[1];
    double pom2 = (*Sruba2_globalne).at(0)[1];
    unsigned int i;

    for (i = 1; i < (*Kadlub_globalne).size(); ++i) {
        if (max_y < (*Kadlub_globalne).at(i)[1]) {
            max_y = (*Kadlub_globalne).at(i)[1];
        }
    }
    for (i = 1; i < (*Sruba1_globalne).size(); ++i) {
        if (pom1 < (*Sruba1_globalne).at(i)[1]) {
            pom1 = (*Sruba1_globalne).at(i)[1];
        }
    }
    for (i = 1; i < (*Sruba2_globalne).size(); ++i) {
        if (pom2 < (*Sruba2_globalne).at(i)[1]) {
            pom2 = (*Sruba2_globalne).at(i)[1];
        }
    }
    if (max_y > pom1) {
        if (max_y > pom2) {
            return max_y;
        } else {
            return pom2;
        }
    } else {
        if (pom1 > pom2) {
            return pom1;
        } else {
            return pom2;
        }
    }
    return max_y;
}



/*!
 * Zwraca najmniejszą wartość 
 * wspołrzędnej y wśród punktów 
 * w globalnym układzie odniesienia
 * zarówno kadłuba i śrub.
 * \pre Kontenery przechowujące zbiory
 *      puntków w globalnym układzie
 *      odniesienia muszą zawierać dane.
 * \return Zwraca najmniejszą wartość 
 *         wspołrzędnej y wśród punktów 
 *         w globalnym układzie odniesienia
 *         zarówno kadłuba i śrub.  
 */
double Dron::zwroc_min_y () {
    std::vector<Wektor3D> * Kadlub_globalne = _Kadlub.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba1_globalne = _Sruba1.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba2_globalne = _Sruba2.zwroc_wskaznik_do_globalnych();
    double min_y = (*Kadlub_globalne).at(0)[1];
    double pom1 = (*Sruba1_globalne).at(0)[1];
    double pom2 = (*Sruba2_globalne).at(0)[1];
    unsigned int i;

    for (i = 1; i < (*Kadlub_globalne).size(); ++i) {
        if (min_y > (*Kadlub_globalne).at(i)[1]) {
            min_y = (*Kadlub_globalne).at(i)[1];
        }
    }
    for (i = 1; i < (*Sruba1_globalne).size(); ++i) {
        if (pom1 > (*Sruba1_globalne).at(i)[1]) {
            pom1 = (*Sruba1_globalne).at(i)[1];
        }
    }
    for (i = 1; i < (*Sruba2_globalne).size(); ++i) {
        if (pom2 > (*Sruba2_globalne).at(i)[1]) {
            pom2 = (*Sruba2_globalne).at(i)[1];
        }
    }
    if (min_y < pom1) {
        if (min_y < pom2) {
            return min_y;
        } else {
            return pom2;
        }
    } else {
        if (pom1 < pom2) {
            return pom1;
        } else {
            return pom2;
        }
    }
    return min_y;
}



/*!
 * Zwraca największą wartość 
 * wspołrzędnej z wśród punktów 
 * w globalnym układzie odniesienia
 * zarówno kadłuba i śrub.
 * \pre Kontenery przechowujące zbiory
 *      puntków w globalnym układzie
 *      odniesienia muszą zawierać dane.
 * \return Zwraca największą wartość 
 *         wspołrzędnej z wśród punktów 
 *         w globalnym układzie odniesienia
 *         zarówno kadłuba i śrub.  
 */
double Dron::zwroc_max_z () {
    std::vector<Wektor3D> * Kadlub_globalne = _Kadlub.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba1_globalne = _Sruba1.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba2_globalne = _Sruba2.zwroc_wskaznik_do_globalnych();
    double max_z = (*Kadlub_globalne).at(0)[2];
    double pom1 = (*Sruba1_globalne).at(0)[2];
    double pom2 = (*Sruba2_globalne).at(0)[2];
    unsigned int i;

    for (i = 1; i < (*Kadlub_globalne).size(); ++i) {
        if (max_z < (*Kadlub_globalne).at(i)[2]) {
            max_z = (*Kadlub_globalne).at(i)[2];
        }
    }
    for (i = 1; i < (*Sruba1_globalne).size(); ++i) {
        if (pom1 < (*Sruba1_globalne).at(i)[2]) {
            pom1 = (*Sruba1_globalne).at(i)[2];
        }
    }
    for (i = 1; i < (*Sruba2_globalne).size(); ++i) {
        if (pom2 < (*Sruba2_globalne).at(i)[2]) {
            pom2 = (*Sruba2_globalne).at(i)[2];
        }
    }
    if (max_z > pom1) {
        if (max_z > pom2) {
            return max_z;
        } else {
            return pom2;
        }
    } else {
        if (pom1 > pom2) {
            return pom1;
        } else {
            return pom2;
        }
    }
    return max_z;
}



/*!
 * Zwraca najmniejszą wartość 
 * wspołrzędnej z wśród punktów 
 * w globalnym układzie odniesienia
 * zarówno kadłuba i śrub.
 * \pre Kontenery przechowujące zbiory
 *      puntków w globalnym układzie
 *      odniesienia muszą zawierać dane.
 * \return Zwraca najmniejszą wartość 
 *         wspołrzędnej z wśród punktów 
 *         w globalnym układzie odniesienia
 *         zarówno kadłuba i śrub.  
 */
double Dron::zwroc_min_z () {
    std::vector<Wektor3D> * Kadlub_globalne = _Kadlub.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba1_globalne = _Sruba1.zwroc_wskaznik_do_globalnych();
    std::vector<Wektor3D> * Sruba2_globalne = _Sruba2.zwroc_wskaznik_do_globalnych();
    double min_z = (*Kadlub_globalne).at(0)[2];
    double pom1 = (*Sruba1_globalne).at(0)[2];
    double pom2 = (*Sruba2_globalne).at(0)[2];
    unsigned int i;

    for (i = 1; i < (*Kadlub_globalne).size(); ++i) {
        if (min_z > (*Kadlub_globalne).at(i)[2]) {
            min_z = (*Kadlub_globalne).at(i)[2];
        }
    }
    for (i = 1; i < (*Sruba1_globalne).size(); ++i) {
        if (pom1 > (*Sruba1_globalne).at(i)[2]) {
            pom1 = (*Sruba1_globalne).at(i)[2];
        }
    }
    for (i = 1; i < (*Sruba2_globalne).size(); ++i) {
        if (pom2 > (*Sruba2_globalne).at(i)[2]) {
            pom2 = (*Sruba2_globalne).at(i)[2];
        }
    }
    if (min_z < pom1) {
        if (min_z < pom2) {
            return min_z;
        } else {
            return pom2;
        }
    } else {
        if (pom1 < pom2) {
            return pom1;
        } else {
            return pom2;
        }
    }
    return min_z;
}



/*!
 * Sprawdza czy nastąpiła kolizja drona z przeszkodą.
 * \param [in] zbior_przeszkod - zbiór przeszkód, 
 *        z którymi zostanie sprawdzona kolizyjność.
 * \pre Kontener przechowujący zbiór przeszkód
 *      musi zawierać dane.
 * \return Zwraca true jeśli nastąpiła kolizja z
 *         którąkolwiek przeszkodą, a false 
 *         jeśli nie nastąpiła z żadną.
 */
bool Dron::czy_kolizja (std::vector<std::shared_ptr<Odcinek>> zbior_przeszkod)
{
    std::vector<std::shared_ptr<Odcinek>>::const_iterator I;
    double P_max_x, P_min_x, P_max_y, P_min_y, P_max_z, P_min_z;
    double D_max_x = zwroc_max_x();
    double D_min_x = zwroc_min_x();
    double D_max_y = zwroc_max_y();
    double D_min_y = zwroc_min_y();
    double D_max_z = zwroc_max_z();
    double D_min_z = zwroc_min_z();

    for (I = zbior_przeszkod.begin(); I != zbior_przeszkod.end(); ++I)
    {
        P_max_x = (**I).zwroc_max_x();
        P_min_x = (**I).zwroc_min_x();
        P_max_y = (**I).zwroc_max_y();
        P_min_y = (**I).zwroc_min_y();
        P_max_z = (**I).zwroc_max_z();
        P_min_z = (**I).zwroc_min_z();
        
        if ((D_min_x < P_max_x && P_min_x < D_max_x) && (D_min_y < P_max_y && P_min_y < D_max_y) && (D_min_z < P_max_z && P_min_z < D_max_z))
        {
            return true;
        }
    }
    
    return false;
}