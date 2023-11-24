#include <iostream>
#include "Liste.h"

using namespace std;

template <typename T>
Liste<T>::Liste()
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Liste>" << endl;
#endif

    this->tete = nullptr;
    this->taille = 0;
}

template <typename T>
Liste<T>::~Liste()
{
#ifdef MAP
    cout << "Appel au destructeur de <Liste>" << endl;
#endif

    delete tete;
}

template <typename T>
int Liste<T>::getTaille() const
{
    return taille;
}

template <typename T>
void Liste<T>::ajouter(T valeur)
{
    // On crée un nouveau maillon avec la valeur passée en paramètre (il sera placé à la fin de la liste)
    Maillon *nouveauMaillon = new Maillon(valeur, nullptr);

    // Si la liste est vide, on ajoute le nouveau maillon en tête
    if (tete == nullptr)
    {
        tete = nouveauMaillon;
    }
    else
    {
        Maillon *courrent = tete;
        while (courrent->suivant != nullptr)
        {
            courrent = courrent->suivant;
        }
        courrent->suivant = nouveauMaillon;
    }
    taille++;
}

template <typename T>
bool Liste<T>::rechercher(const T *valeur) const
{
    Maillon *courrent = tete;
    while (courrent != nullptr)
    {
        if (courrent->valeur == valeur)
        {
            return true;
        }
        courrent = courrent->suivant;
    }
    return false;
}

template <typename T>
void Liste<T>::afficher() const
{
    Maillon *courrent = tete;
    while (courrent != nullptr)
    {
        T.afficher(); // Ici, on suppose que la classe T possède une méthode afficher()
        endl;
        courrent = courrent->suivant;
    }
}