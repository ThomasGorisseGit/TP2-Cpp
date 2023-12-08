#if !defined(MAILLON_H)
#define MAILLON_H
#include <iostream>
using namespace std;

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
    Maillon(T *valeur = nullptr, Maillon *suivant = nullptr);
    
    T* getValeur() const;
    
    Maillon<T>* getSuivant() const;
    inline void setSuivant(Maillon<T> *suivant) { this->suivant = suivant; }
    void Afficher() const;

    /**
     * @brief Destructeur de la classe Maillon
     *
     */
    virtual ~Maillon();

private:
    T *valeur;
    Maillon *suivant;
};


template <typename T>
Maillon<T>::Maillon(T *valeur, Maillon *suivant)
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
}

template <typename T>
T* Maillon<T>::getValeur() const
{
    return valeur;
}


template <typename T>
Maillon<T>* Maillon<T>::getSuivant() const
{
    return suivant;
}

template <typename T>
void Maillon<T>::Afficher() const
{
    this->valeur->Afficher(); //on suppose que l'élement dans le maillon possède une méthode afficher
}
#endif // MAILLON_H