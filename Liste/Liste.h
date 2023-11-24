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
     * @brief Retourne la taille de la liste
     *
     */
    int getTaille() const;

    /**
     * @brief Ajoute un élément à la fin de la liste chaînée
     *
     * @param valeur Le Trajet à ajouter à la liste
     */
    void ajouter(T valeur);

    /**
     * @brief Permet de rechercher un Trajet dans la liste
     *
     * @param valeur Le Trajet à rechercher dans la liste
     */
    bool rechercher(const T *valeur) const;

    /**
     * @brief Permet d'afficher la liste
     *
     */
    void afficher() const;

protected:
    int taille;
    Maillon *tete;
};

#endif // LISTE_H