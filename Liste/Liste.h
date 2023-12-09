#if !defined(LISTE_H)
#define LISTE_H

#include <iostream>
#include "./Maillon.h"

using namespace std;

template <typename T>
class Liste
{
public:
    Liste();
    // Constructeur par défaut de la classe Liste
    // Mode d'emploi :
    //       Appel du constructeur par défaut de la classe Liste avec Liste<T> liste;

    virtual ~Liste();
    // Destructeur de la classe Liste

    T *GetValeur(unsigned int index) const;
    // Méthode permettant de retourner la valeur du maillon à l'index passé en paramètre
    // Il prend en paramètre l'index du maillon dont on veut la valeur
    // Mode d'emploi :
    //       Appel de la méthode avec liste.GetValeur(index);

    unsigned int GetTaille() const;
    // Méthode permettant de retourner la taille de la liste
    // Mode d'emploi :
    //       Appel de la méthode avec int taille=liste.GetTaille();

    void Ajouter(T *valeur);
    // Méthode permettant d'ajouter un élément à la fin de la liste chaînée
    // Il prend en paramètre le trajet à ajouter à la liste
    // Mode d'emploi :
    //       Appel de la méthode avec liste.Ajouter(trajet);

    void Ajouter(Liste<T> *liste);
    // Méthode permettant d'ajouter une liste à la fin de la liste chaînée
    // Il prend en paramètre la liste à ajouter à la liste
    // Mode d'emploi :
    //       Appel de la méthode avec liste.Ajouter(liste);

    bool Rechercher(const T *valeur) const;
    // Méthode permettant de rechercher un trajet dans la liste
    // Il prend en paramètre le trajet à rechercher dans la liste
    // Il retourne true si le trajet est présent dans la liste, false sinon
    // Mode d'emploi :
    //       Appel de la méthode avec liste.Rechercher(trajet);

    void Afficher() const;
    // Méthode permettant d'afficher la liste
    // Mode d'emploi :

    void Erase(unsigned int index);
    // Méthode permettant de supprimer l'élément à l'index spécifié de la liste
    // Mode d'emploi :
    //       Appel de la méthode avec liste.Erase(index);

protected:
    unsigned int taille;
    Maillon<T> *tete;
};

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
    Maillon<T> *courrent = tete;
    while (courrent != nullptr)
    {
        Maillon<T> *suivant = courrent->getSuivant();
        delete courrent;
        courrent = suivant;
    }
}

template <typename T>
T *Liste<T>::GetValeur(unsigned int index) const
{
    Maillon<T> *courrent = tete;
    unsigned int i = 0;
    while (courrent != nullptr)
    {
        if (i == index)
        {
            return courrent->getValeur();
        }
        courrent = courrent->getSuivant();
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
void Liste<T>::Ajouter(T *valeur)
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
        while (courrent->getSuivant() != nullptr)
        {
            courrent = courrent->getSuivant();
        }
        courrent->setSuivant(nouveauMaillon);
    }
    taille++;
}

template <typename T>
void Liste<T>::Ajouter(Liste<T> *liste)
{
    for (unsigned int i = 0; i < liste->GetTaille(); i++)
    {
        this->Ajouter(liste->GetValeur(i));
    }
}

template <typename T>
bool Liste<T>::Rechercher(const T *valeur) const
{
    Maillon<T> *courrent = tete;
    while (courrent != nullptr)
    {
        if (courrent->getValeur() == valeur)
        {
            return true;
        }
        courrent = courrent->getSuivant();
    }
    return false;
}

template <typename T>
void Liste<T>::Afficher() const
{
    Maillon<T> *courrent = tete;
    while (courrent != nullptr)
    {
        courrent->Afficher(); // Ici, on suppose que la classe T possède une méthode afficher()
        courrent = courrent->getSuivant();
    }
}

template <typename T>
void Liste<T>::Erase(unsigned int index)
{
    // Vérifiez si l'index est valide
    if (index >= taille)
    {
        cout << "Index hors de la plage de la liste." << endl;
        return;
    }

    // Cas particulier : suppression de la tête de liste
    if (index == 0)
    {
        Maillon<T> *temp = tete;
        tete = tete->getSuivant();
        delete temp;
        taille--;
        return;
    }

    // Parcours de la liste pour trouver le maillon précédant celui à supprimer
    Maillon<T> *precedent = nullptr;
    Maillon<T> *courrent = tete;
    unsigned int i = 0;

    while (i < index)
    {
        precedent = courrent;
        courrent = courrent->getSuivant();
        i++;
    }

    // Suppression du maillon à l'index spécifié
    precedent->setSuivant(courrent->getSuivant());
    delete courrent;
    taille--;
}


#endif // LISTE_H
