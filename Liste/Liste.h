#if !defined(LISTE_H)
#define LISTE_H

#include <iostream>
#include "./Maillon.h"

using namespace std;

template <typename T>
class Liste
{
public:
    /**
     * @brief Constructeur par défaut de la classe Liste
     *
     */
    Liste();

    /**
     * @brief Destructeur de la classe Liste
     *
     */
    virtual ~Liste();

    /**
     * @brief Retourne la valeur du maillon à l'index passé en paramètre
     *
     * @param index L'index du maillon dont on veut la valeur
     */
    T* GetValeur(unsigned int index) const;

    /**
     * @brief Retourne la taille de la liste
     *
     * @return La taille de la liste
     */
    unsigned int GetTaille() const;

    /**
     * @brief Ajoute un élément à la fin de la liste chaînée
     *
     * @param valeur Le Trajet à ajouter à la liste
     */
    void Ajouter(T* valeur);

    void Ajouter(Liste<T> * liste);

    /**
     * @brief Permet de rechercher un Trajet dans la liste
     *
     * @param valeur Le Trajet à rechercher dans la liste
     * @return true Si le Trajet est présent dans la liste, false sinon
     */
    bool Rechercher(const T *valeur) const;

    /**
     * @brief Permet d'afficher la liste
     *
     */
    void Afficher() const;

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
    // TODO : vérifier que ça marche
    Maillon<T> *courrent = tete;
    while (courrent != nullptr)
    {
        Maillon<T> *suivant = courrent->getSuivant();
        delete courrent;
        courrent = suivant;
    }
}

template <typename T>
T* Liste<T>::GetValeur(unsigned int index) const
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
void Liste<T>::Ajouter(T* valeur)
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
void Liste<T>::Ajouter(Liste<T> * liste){
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
        courrent->Afficher(); // Ici, on suppose que la classe T possède une méthode Afficher()
        courrent = courrent->getSuivant();
    }
}

#endif // LISTE_H
