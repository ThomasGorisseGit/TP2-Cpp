#if !defined(MAILLON_H)
#define MAILLON_H
#include <iostream>

template <typename T>
class Maillon
{
public:
    /**
     * @brief Constructeur de la classe Maillon
     *
     * @param valeur Le Trajet lié au maillon
     * @param suivant Le maillon suivant
     */
    Maillon(const T *valeur = nullptr, Maillon *suivant = nullptr);

    /**
     * @brief Destructeur de la classe Maillon
     *
     */
    virtual ~Maillon();

private:
    T *valeur;
    Maillon *suivant;
};

#endif // MAILLON_H