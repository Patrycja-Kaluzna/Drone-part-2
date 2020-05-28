#include "powierzchnia.hh"



/*!
 * Pozwala na dostęp do kontenera zawierającego
 * zbiór punktów w lokalnym układzie odniesienia.
 * \return Zwraca wskaźnik na konterer zawierający
 *          punkty lokalne.
 */ 
std::vector<Wektor3D> * Powierzchnia::get_Punkty_lokalne ()
{
    std::vector<Wektor3D> * pomWsk = &_Punkty_lokalne;

    return pomWsk;
}



std::vector<Wektor3D>::const_iterator Powierzchnia::wez_Punkty_lokalne () const
{
    std::vector<Wektor3D>::const_iterator I = _Punkty_lokalne.begin();

    return I;
}



std::vector<Wektor3D>::iterator Powierzchnia::set_Punkty_lokalne ()
{
    std::vector<Wektor3D>::iterator I = _Punkty_lokalne.begin();

    return I;
}



/*!
 * Wczytuje ze strumienia plikowego zbiór punktów
 * w lokalnym układzie odniesienia.
 * \param [in] Fstr - strumień plikowy, z którego
 *              zostaną wczytane punkty lokalne.
 * \param [in] Pow - powierzchnia, której punkty
 *              lokalne zostaną wczytane.
 * \pre Fstr i Pow muszą być przekazane przez 
 *              referencję.
 * \return Zwraca strumień plikowy.
 */
std::ifstream & operator >> (std::ifstream & Fstr, Powierzchnia & Pow)
{
    std::vector<Wektor3D> * pomWsk = Pow.get_Punkty_lokalne();
    Wektor3D pomWek;

    while (Fstr.eof() == false)
    {
        Fstr >> pomWek;
        pomWsk->push_back(pomWek);
    }

    return Fstr;
}