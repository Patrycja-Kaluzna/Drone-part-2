#include "odcinek.hh"



/*!
 * Umożliwia czytanie puntków w
 * lokalnym układzie odniesienia.
 * \return Zwraca stały iterator na początek 
 *         kontenera zawierającego zbiór 
 *         punktów w lokalnym układzie 
 *         odniesienia.
 */
std::vector<Wektor3D>::const_iterator Odcinek::get_Punkty_lokalne () const
{
    std::vector<Wektor3D>::const_iterator I = _Punkty_lokalne.begin();

    return I;
}



/*!
 * Umożliwia wczytywanie punktów w
 * lokalnym układzie odniesienia.
 * \return Zwraca iterator na początek 
 *         kontenera zawierającego zbiór 
 *         punktów w lokalnym układzie 
 *         odniesienia.
 */
std::vector<Wektor3D>::iterator Odcinek::set_Punkty_lokalne ()
{
    std::vector<Wektor3D>::iterator I = _Punkty_lokalne.begin();

    return I;
}



/*!
 * Pozwala na dostęp do punktów 
 * w lokalnym układzie odniesienia.
 * \return Zwraca wskaźnik do konterera 
 *         zawierającego zbiór punktów w
 *         lokalnym układzie odniesienia.
 */ 
std::vector<Wektor3D> * Odcinek::zwroc_wskaznik_do_lokalnych ()
{
    std::vector<Wektor3D> * pomWsk = &_Punkty_lokalne;

    return pomWsk;
}



/*!
 * Pozwala na dostęp do punktów 
 * w globalnym układzie odniesienia.
 * \return Zwraca wskaźnik do konterera 
 *         zawierającego zbiór punktów w
 *         globalnym układzie odniesienia.
 */
std::vector<Wektor3D> * Odcinek::zwroc_wskaznik_do_globalnych ()
{
    std::vector<Wektor3D> * pomWsk = &_Punkty_globalne;

    return pomWsk;
}



/*!
 * Zwraca największą wartość 
 * wspołrzędnej x wśród punktów 
 * w globalnym układzie odniesienia.
 * \pre Kontener przechowujący zbiór
 *      puntków w globalnym  układzie
 *      odniesienia musi zawierać dane.
 * \return Zwraca największą wartość 
 *         wspołrzędnej x wśród punktów 
 *         w globalnym układzie odniesienia.  
 */
double Odcinek::zwroc_max_x ()
{
    double max_x = _Punkty_globalne[0][0];
    unsigned int i;

    for (i = 1; i < _Punkty_globalne.size(); ++i)
    {
        if (max_x < _Punkty_globalne[i][0])
        {
            max_x = _Punkty_globalne[i][0];
        }
    }

    return max_x;
}



/*!
 * Zwraca najmniejszą wartość 
 * wspołrzędnej x wśród punktów 
 * w globalnym układzie odniesienia.
 * \pre Kontener przechowujący zbiór
 *      puntków w globalnym  układzie
 *      odniesienia musi zawierać dane.
 * \return Zwraca najmniejszą wartość 
 *         wspołrzędnej x wśród punktów 
 *         w globalnym układzie odniesienia.  
 */
double Odcinek::zwroc_min_x ()
{
    double min_x = _Punkty_globalne[0][0];
    unsigned int i;

    for (i = 1; i < _Punkty_globalne.size(); ++i)
    {
        if (min_x > _Punkty_globalne[i][0])
        {
            min_x = _Punkty_globalne[i][0];
        }
    }

    return min_x;
}



/*!
 * Zwraca największą wartość 
 * wspołrzędnej y wśród punktów 
 * w globalnym układzie odniesienia.
 * \pre Kontener przechowujący zbiór
 *      puntków w globalnym  układzie
 *      odniesienia musi zawierać dane.
 * \return Zwraca największą wartość 
 *         wspołrzędnej y wśród punktów 
 *         w globalnym układzie odniesienia.  
 */
double Odcinek::zwroc_max_y ()
{
    double max_y = _Punkty_globalne[0][1];
    unsigned int i;

    for (i = 1; i < _Punkty_globalne.size(); ++i)
    {
        if (max_y < _Punkty_globalne[i][1])
        {
            max_y = _Punkty_globalne[i][1];
        }
    }

    return max_y;
}



/*!
 * Zwraca najmniejszą wartość 
 * wspołrzędnej y wśród punktów 
 * w globalnym układzie odniesienia.
 * \pre Kontener przechowujący zbiór
 *      puntków w globalnym  układzie
 *      odniesienia musi zawierać dane.
 * \return Zwraca najmniejszą wartość 
 *         wspołrzędnej y wśród punktów 
 *         w globalnym układzie odniesienia.  
 */
double Odcinek::zwroc_min_y ()
{
    double min_y = _Punkty_globalne[0][1];
    unsigned int i;

    for (i = 1; i < _Punkty_globalne.size(); ++i)
    {
        if (min_y > _Punkty_globalne[i][1])
        {
            min_y = _Punkty_globalne[i][1];
        }
    }

    return min_y;
}



/*!
 * Zwraca największą wartość 
 * wspołrzędnej z wśród punktów 
 * w globalnym układzie odniesienia.
 * \pre Kontener przechowujący zbiór
 *      puntków w globalnym  układzie
 *      odniesienia musi zawierać dane.
 * \return Zwraca największą wartość 
 *         wspołrzędnej z wśród punktów 
 *         w globalnym układzie odniesienia.  
 */
double Odcinek::zwroc_max_z ()
{
    double max_z = _Punkty_globalne[0][2];
    unsigned int i;

    for (i = 1; i < _Punkty_globalne.size(); ++i)
    {
        if (max_z < _Punkty_globalne[i][2])
        {
            max_z = _Punkty_globalne[i][2];
        }
    }

    return max_z;
}



/*!
 * Zwraca najmniejszą wartość 
 * wspołrzędnej z wśród punktów 
 * w globalnym układzie odniesienia.
 * \pre Kontener przechowujący zbiór
 *      puntków w globalnym  układzie
 *      odniesienia musi zawierać dane.
 * \return Zwraca najmniejszą wartość 
 *         wspołrzędnej z wśród punktów 
 *         w globalnym układzie odniesienia.  
 */
double Odcinek::zwroc_min_z ()
{
    double min_z = _Punkty_globalne[0][2];
    unsigned int i;

    for (i = 1; i < _Punkty_globalne.size(); ++i)
    {
        if (min_z > _Punkty_globalne[i][2])
        {
            min_z = _Punkty_globalne[i][2];
        }
    }

    return min_z;
}



/*!
 * Wczytuje zbiór punktów w 
 * lokalnym układzie odniesienia
 * ze strumienia plikowego.
 * \param [in] Fstr - strumień plikowy,
 *        z którego punkty lokalne 
 *        zostaną wczytane.
 * \param [in] Odc - odcinek, którego 
 *        punkty lokalne zostaną wczytane.
 * \pre Parametry Fstr i Odc muszą być
 *      przekazane  przez referencję.
 * \return Zwraca strumień plikowy.
 */
std::ifstream & operator >> (std::ifstream & Fstr, Odcinek & Odc)
{
    std::vector<Wektor3D> * pomWsk = Odc.zwroc_wskaznik_do_lokalnych();
    Wektor3D pomWek;

    while (Fstr.eof() == false)
    {
        Fstr >> pomWek;
        pomWsk->push_back(pomWek);
    }

    return Fstr;
}



/*!
 * Zapisuje zbiór punktów w 
 * lokalnym układzie odniesienia
 * na strumieniu plikowym.
 * \param [in] Fstr - strumień plikowy,
 *        na którym punkty lokalne 
 *        zostaną zapisane.
 * \param [in] Odc - odcinek, którego 
 *        punkty lokalne zostaną zapisane.
 * \pre Parametry Fstr i Odc muszą być
 *      przekazane  przez referencję.
 * \return Zwraca strumień plikowy.
 */
std::ofstream & operator << (std::ofstream & Fstr, Odcinek & Odc)
{
    std::vector<Wektor3D> * pomWsk = Odc.zwroc_wskaznik_do_lokalnych();
    unsigned int i;

    for (i = 0; i < pomWsk->size(); ++i)
    {
        if (i != (pomWsk->size() - 1))
        {
            Fstr << (*pomWsk)[i] << "\n";
        } else {
            Fstr << (*pomWsk)[i];
        }
    }    

    return Fstr;
}