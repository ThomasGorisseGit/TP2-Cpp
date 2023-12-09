#if !defined(MAILLON_H)
#define MAILLON_H
#include <iostream>
using namespace std;

template <typename T>
class Maillon
{
public:
    Maillon(T *valeur = nullptr, Maillon *suivant = nullptr);
    // Constructeur de la classe Maillon
    // Il prend en paramètre le trajet lié au maillon et le maillon suivant
    // Les valeurs par défaut sont nullptr pour le trajet et le maillon suivant
    // Mode d'emploi :
    //       Appel du constructeur avec Maillon<T> maillon;

    T *getValeur() const;
    // Méthode permettant de retourner la valeur du maillon
    // Mode d'emploi :
    //       Appel de la méthode avec Mailon<T> maillon = maillon.getValeur();

    Maillon<T> *getSuivant() const;
    // Méthode permettant de retourner le maillon suivant
    // Mode d'emploi :
    //       Appel de la méthode avec Mailon<T> maillon = maillon.getSuivant();

    inline void setSuivant(Maillon<T> *suivant) { this->suivant = suivant; }
    // Méthode permettant de modifier le maillon suivant
    // Methode définie avec inline pour optimiser le code
    // Mode d'emploi :
    //       Appel de la méthode avec maillon.setSuivant(suivant);

    virtual ~Maillon();
    // Destructeur de la classe Maillon

private:
    T *valeur;
    // Valeur du maillon
    Maillon *suivant;
    // Pointeur vers le maillon suivant
};

template <typename T>
Maillon<T>::Maillon(T *valeur, Maillon *suivant)
// Constructeur de la classe Maillon
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Maillon>" << endl;
#endif

    this->valeur = valeur;
    this->suivant = suivant;
} //----- Fin de Maillon

template <typename T>
Maillon<T>::~Maillon()
// Destructeur de la classe Maillon
{
#ifdef MAP
    cout << "Appel au destructeur de <Maillon>" << endl;
#endif

    delete valeur;
} //----- Fin de ~Maillon

template <typename T>
T *Maillon<T>::getValeur() const
// Méthode permettant de retourner la valeur du maillon
{
    return valeur;
} // Fin de la méthode GetValeur

template <typename T>
Maillon<T> *Maillon<T>::getSuivant() const
// Méthode permettant de retourner le maillon suivant
{
    return suivant;
} // Fin de la méthode GetSuivant
#endif // MAILLON_H