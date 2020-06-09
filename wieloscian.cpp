#include "wieloscian.hh"



/*!
 * Ustawia wartości pól _Kat_orientacjiX, _Kat_orientacjiY
 * i _Kat_orientacjiZ na 0, _Macierz_rotacji jako macierz obrotu 
 * wokół osi Z oraz _ostatnia_zmiana_orientacji na z. 
 */
Wieloscian::Wieloscian ()
{
    _Kat_orientacjiX = 0;
    _Kat_orientacjiY = 0;
    _Kat_orientacjiZ = 0;

    _Macierz_rotacji(0,0) = cos(_Kat_orientacjiZ);
    _Macierz_rotacji(0,1) = -sin(_Kat_orientacjiZ);
    _Macierz_rotacji(0,2) = 0;
    _Macierz_rotacji(1,0) = sin(_Kat_orientacjiZ);
    _Macierz_rotacji(1,1) = cos(_Kat_orientacjiZ);
    _Macierz_rotacji(1,2) = 0;
    _Macierz_rotacji(2,0) = 0;
    _Macierz_rotacji(2,1) = 0;
    _Macierz_rotacji(2,2) = 1;

    _ostatnia_zmiana_orientacji = 'z';
}



/*!
 * Wczytuje zbiór punktów w globalnym układzie odniesienia,
 * przepisując je z kontenera zawierającego punkty lokalne
 * z dodanym do nich wektorem translacji.
 */
void Wieloscian::wczytaj_globalne ()
{
    unsigned int i;

    for (i = 0; i < _Punkty_lokalne.size(); ++i)
    {
        _Punkty_globalne.push_back(_Punkty_lokalne[i] + _Wektor_translacji);    
    }
}



/*!
 * Umożliwia czytanie puntków w
 * globalnym układzie odniesienia.
 * \return Zwraca stały iterator na początek 
 *         kontenera zawierającego zbiór 
 *         punktów w globalnym układzie 
 *         odniesienia.
 */
std::vector<Wektor3D>::const_iterator Wieloscian::get_Punkty_globalne () const
{
    std::vector<Wektor3D>::const_iterator I = _Punkty_globalne.begin();

    return I;
}



/*!
 * Umożliwia wczytywanie punktów w
 * globalnym układzie odniesienia.
 * \return Zwraca iterator na początek 
 *         kontenera zawierającego zbiór 
 *         punktów w globalnym układzie 
 *         odniesienia.
 */
std::vector<Wektor3D>::iterator Wieloscian::set_Punkty_globalne ()
{
    std::vector<Wektor3D>::iterator I = _Punkty_globalne.begin();

    return I;
}



/*!
 * Zwraca liczbę elementów kontenera z puntkami globalnymi.
 * \return Zwraca liczbę elementów kontenera z puntkami globalnymi.
 */
unsigned int Wieloscian::liczba_Punktow_globalnych () const
{
    int pom;

    pom = _Punkty_globalne.size();

    return pom;
}



/*!
 * Ustawia wartość pola _Kat_orientacji odpowiednio X, Y 
 * lub Z na zadaną pierwszym parametrem.
 * \param [in] kat - kąt orientacji, który zostanie 
 *        ustawiony.
 * \param [in] wymiar - wymiar, w którym zostanie 
 *        ustawiony kąt orientacji.
 * \pre Kąt orientacji przekazany przez pierwszy parametr
 *      powinnen zostać podany w stopniach (metoda 
 *      przelicza go na radiany). 
 */
void Wieloscian::ustaw_Kat_orientacji (double kat, char wymiar)
{
    switch (wymiar)
    {
        case 'x':
        {
            _Kat_orientacjiX += (kat * M_PI / 180);
            break;
        }
        case 'y':
        {
            _Kat_orientacjiY += (kat * M_PI / 180);
            break;
        }
        case 'z':
        {
            _Kat_orientacjiZ += (kat * M_PI / 180);
            break;
        }
    }
}



/*!
 * Oblicza macierz obrotu wokół osi odpowiednio X, Y lub Z
 * wykorzystując wartość pola _Kat_orientacji też
 * odpowiednio X, Y lub Z.
 * \param [in] wymiar - wymiar, w którym zostanie 
 *        obliczona macierz obrotu.
 * \return Zwraca obliczoną macierz obrotu w 
 *         zadanym wymiarze.
 */
Macierz3x3 Wieloscian::oblicz_Macierz_rotacji (char wymiar) const
{
    Macierz3x3 pomMac;

    switch (wymiar)
    {
        case 'x':
        {
            pomMac(0,0) = 1;
            pomMac(0,1) = 0;
            pomMac(0,2) = 0;
            pomMac(1,0) = 0;
            pomMac(1,1) = cos(_Kat_orientacjiX);
            pomMac(1,2) = -sin(_Kat_orientacjiX);
            pomMac(2,0) = 0;
            pomMac(2,1) = sin(_Kat_orientacjiX);
            pomMac(2,2) = cos(_Kat_orientacjiX);
            break;
        }
        case 'y':
        {
            pomMac(0,0) = cos(_Kat_orientacjiY);
            pomMac(0,1) = 0;
            pomMac(0,2) = sin(_Kat_orientacjiY);
            pomMac(1,0) = 0;
            pomMac(1,1) = 1;
            pomMac(1,2) = 0;
            pomMac(2,0) = -sin(_Kat_orientacjiY);
            pomMac(2,1) = 0;
            pomMac(2,2) = cos(_Kat_orientacjiY);
            break;
        }
        case 'z':
        {
            pomMac(0,0) = cos(_Kat_orientacjiZ);
            pomMac(0,1) = -sin(_Kat_orientacjiZ);
            pomMac(0,2) = 0;
            pomMac(1,0) = sin(_Kat_orientacjiZ);
            pomMac(1,1) = cos(_Kat_orientacjiZ);
            pomMac(1,2) = 0;
            pomMac(2,0) = 0;
            pomMac(2,1) = 0;
            pomMac(2,2) = 1;
            break;
        }
    }
    
    return pomMac;
}



/*!
 * Ustawia wartość pola _Macierz_rotacji jako 
 * macierz obrotu wokół osi odpowiednio X, Y,
 * Z lub złożenie ich.
 * \param [in] wymiar - wymiar, w którym zostanie 
 *        ustawiona lub domnożona macierz obrotu.
 */
void Wieloscian::ustaw_Macierz_rotacji (char wymiar)
{
    Macierz3x3 pomMac1 = oblicz_Macierz_rotacji(wymiar);
    Macierz3x3 pomMac2 = oblicz_Macierz_rotacji(_ostatnia_zmiana_orientacji);

    if (_ostatnia_zmiana_orientacji == wymiar)
    {
        _Macierz_rotacji = pomMac1;
    } else {
        _Macierz_rotacji = pomMac2 * pomMac1;
    }
}



/*!
 * Oblicza wektor przemieszczenia na zadaną odległość
 * w zależności od orientacji wielościanu.
 * \param [in] odleglosc - odległość, na którą ma
 *        przemieścić się wielościan.
 * \return Zwraca obliczony wektor przemieszczenia
 *         na zadaną odległość.
 */
Wektor3D Wieloscian::oblicz_Wektor_przemieszczenia (double odleglosc) const
{
    Wektor3D pomWek;

    switch (_ostatnia_zmiana_orientacji)
    {
        case 'x':
        {
            pomWek[0] = odleglosc * cos(_Kat_orientacjiX + 90 * M_PI / 180); 
            pomWek[1] = odleglosc * sin(_Kat_orientacjiX + 90 * M_PI / 180); 
            pomWek[2] = 0;
            break;
        }
        case 'y':
        {
            pomWek[0] = odleglosc * cos(_Kat_orientacjiY + 90 * M_PI / 180); 
            pomWek[1] = odleglosc * sin(_Kat_orientacjiY + 90 * M_PI / 180); 
            pomWek[2] = 0;
            break;
        }
        case 'z':
        {
            pomWek[0] = odleglosc * cos(_Kat_orientacjiZ + 90 * M_PI / 180); 
            pomWek[1] = odleglosc * sin(_Kat_orientacjiZ + 90 * M_PI / 180); 
            pomWek[2] = 0;
            break;
        }
    }

    return pomWek;
}



/*!
 * Uaktualnia wartość pola _Wektor_translacji 
 * o zadaną odległość.
 * \param [in] odleglosc - odległość, o którą ma
 *        zostać uaktualniony wektor translacji.
 */
void Wieloscian::ustaw_Wektor_translacji (double odleglosc)
{
    Wektor3D pomWek = oblicz_Wektor_przemieszczenia(odleglosc);

    _Wektor_translacji = _Wektor_translacji + pomWek;
}



/*!
 * Obraca wielościan wokół osi odpowiednio X, Y lub Z 
 * o kąt przekazany przez pierwszy parametr, ustawiając 
 * również wartość pola _Kat_orientacji też odpowiednio 
 * X, Y lub Z oraz wartość pola _Macierz_rotacji.
 * \param [in] kat - kąt, o który ma być 
 *        obrócony wielościan.
 * \param [in] wymiar - wymiar, w którym 
 *        ma być obórócony wielościan.
 */
void Wieloscian::zmiana_orientacji (double kat, char wymiar)
{
    unsigned int i;

    ustaw_Kat_orientacji(kat, wymiar);
    ustaw_Macierz_rotacji(wymiar);

    for (i = 0; i < _Punkty_globalne.size(); ++i)
    { 
        _Punkty_globalne[i] = _Macierz_rotacji * _Punkty_lokalne[i] + _Macierz_rotacji * _Wektor_translacji;
    }
    
    _ostatnia_zmiana_orientacji = wymiar;
}



/*!
 * Porusza wielościan na wprost na odległość przekazaną
 * przez parametr, obliczając odpowiedni wektor 
 * przemieszczenia oraz ustawiając wartość 
 * pola _Wektor_translacji.
 * \param [in] odleglosc - odległość, na którą 
 *        ma przmieścić się wielościan.
 */
void Wieloscian::ruch_na_wprost (double odleglosc)
{
    Wektor3D Wektor_przemieszczenia = oblicz_Wektor_przemieszczenia(odleglosc);
    unsigned int i;

    for (i = 0; i < _Punkty_globalne.size(); ++i)
    {
        _Punkty_globalne[i] = _Punkty_globalne[i] + Wektor_przemieszczenia;
    }

    ustaw_Wektor_translacji(odleglosc);
}