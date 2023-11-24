#include <iostream>
#include "Maillon.h"
using namespace std;

template <typename T>
Maillon<T>::Maillon(const T *valeur, Maillon *suivant)
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Maillon>" << endl;
#endif

    this->valeur = valeur;
    this->suivant = suivant;
}

template <typename T>
Maillon<T>::~Maillon()
{
#ifdef MAP
    cout << "Appel au destructeur de <Maillon>" << endl;
#endif
    delete valeur;
    delete suivant;
}
