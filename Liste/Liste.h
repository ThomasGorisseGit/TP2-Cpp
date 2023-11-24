#if !defined(LISTE_H)
#define LISTE_H

#include <iostream>
#include "Maillon.h"

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
    ~Liste();

    /**
     * @brief Retourne la valeur du maillon à l'index passé en paramètre
     *
     * @param index L'index du maillon dont on veut la valeur
     */
    T GetValeur(unsigned int index) const;

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
    void Ajouter(T valeur);

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

#endif // LISTE_H