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

    void ModifierToutesLesValeursEnNull();
    // Fonction qui vide la liste avant de la supprimer, pour ne pas supprimer des trajets

    Maillon<T> *GetMaillon(unsigned int index) const;
    // Méthode permettant de retourner le maillon à l'index passé en paramètre

protected:
    unsigned int taille;
    Maillon<T> *tete;
};

// ----------------------------- Implémentation des méthodes -----------------------------
// (on ne peut pas séparer l'implémentation de la déclaration pour une classe template)

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
        Maillon<T> *suivant = courrent->GetSuivant();
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
            return courrent->GetValeur(); // Méthode getValeur() de la classe Maillon
        }
        courrent = courrent->GetSuivant();
        i++;
    }
    return nullptr; // Si l'index est invalide, on retourne nullptr
}

template <typename T>
Maillon<T> *Liste<T>::GetMaillon(unsigned int index) const
{
    Maillon<T> *courrent = tete;
    unsigned int i = 0;
    while (courrent != nullptr)
    {
        if (i == index)
        {
            return courrent;
        }
        courrent = courrent->GetSuivant();
        i++;
    }
    return nullptr; // Si l'index est invalide, on retourne nullptr
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
        while (courrent->GetSuivant() != nullptr)
        {
            courrent = courrent->GetSuivant();
        }
        courrent->SetSuivant(nouveauMaillon);
    }
    taille++;
}

template <typename T>
void Liste<T>::Ajouter(Liste<T> *liste)
{
    for (unsigned int i = 0; i < liste->GetTaille(); i++)
    {
        this->Ajouter(liste->GetValeur(i)); // On ajoute maillon par maillon
    }
}

template <typename T>
bool Liste<T>::Rechercher(const T *valeur) const
{
    Maillon<T> *courrent = tete;
    while (courrent != nullptr)
    {
        if (courrent->GetValeur() == valeur)
        {
            return true;
        }
        courrent = courrent->GetSuivant();
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
        courrent = courrent->GetSuivant();
    }
}

template <typename T>
void Liste<T>::Erase(unsigned int index)
{
    // Vérifiez si l'index est valide
    if (index >= taille)
    {
        cout << "Index invalide." << endl;
        return;
    }

    // Cas particulier : suppression de la tête de liste
    if (index == 0)
    {
        Maillon<T> *temp = tete;
        tete = tete->GetSuivant();
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
        courrent = courrent->GetSuivant();
        i++;
    }

    // Suppression du maillon à l'index spécifié
    precedent->SetSuivant(courrent->GetSuivant());
    delete courrent;
    taille--;
}

template <typename T>
void Liste<T>::ModifierToutesLesValeursEnNull()
{
    Maillon<T> *courant = tete;

    while (courant != nullptr)
    {
        courant->ModifierValeur(nullptr);
        courant = courant->GetSuivant();
    }
}
#endif // LISTE_H
