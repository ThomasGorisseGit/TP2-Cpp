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
    // On parcourt la liste et on supprime chaque maillon
    //TODO : vérifier que ça marche
    Maillon<T> *courrent = tete;
    while (courrent != nullptr)
    {
        Maillon<T> *suivant = courrent->suivant;
        delete courrent;
        courrent = suivant;
    }

    delete tete;
}

template <typename T>
T Liste<T>::GetValeur(unsigned int index) const
{
    Maillon<T> *courrent = tete;
    int i = 0;
    while (courrent != nullptr)
    {
        if (i == index)
        {
            return courrent->valeur;
        }
        courrent = courrent->suivant;
        i++;
    }
    return nullptr;
}

template <typename T>
unsigned int Liste<T>::GetTaille() const
{
    return taille;
}

template <typename T>
void Liste<T>::Ajouter(T valeur)
{
    // On crée un nouveau maillon avec la valeur passée en paramètre (il sera placé à la fin de la liste)
    Maillon<T> *nouveauMaillon = new Maillon<T>(valeur, nullptr);

    // Si la liste est vide, on ajoute le nouveau maillon en tête
    if (tete == nullptr)
    {
        tete = nouveauMaillon;
    }
    else
    {
        Maillon<T> *courrent = tete;
        while (courrent->suivant != nullptr)
        {
            courrent = courrent->suivant;
        }
        courrent->suivant = nouveauMaillon;
    }
    taille++;
}

template <typename T>
bool Liste<T>::Rechercher(const T *valeur) const
{
    Maillon<T> *courrent = tete;
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
void Liste<T>::Afficher() const
{
    Maillon<T> *courrent = tete;
    while (courrent != nullptr)
    {
        courrent->afficher(); // Ici, on suppose que la classe T possède une méthode afficher()
        courrent = courrent->suivant;
    }
}