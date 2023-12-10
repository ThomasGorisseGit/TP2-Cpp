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

    void Afficher() const;
    // Méthode permettant d'appeller la méthode Afficher() de la valeur en supposant quelle existe
    // Mode d'emploi :
    //       Appel de la méthode avec Mailon<T> maillon = maillon.Afficher();

    inline void setSuivant(Maillon<T> *suivant) { this->suivant = suivant; }
    // Méthode permettant de modifier le maillon suivant
    // Methode définie avec inline pour optimiser le code
    // Mode d'emploi :
    //       Appel de la méthode avec maillon.setSuivant(suivant);

    virtual ~Maillon();
    // Destructeur de la classe Maillon

    void ModifierValeur(T *nouvelleValeur);
    //Permet de modifier la valeur d'un maillon

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
T *Maillon<T>::getValeur() const
{
    return valeur;
}

template <typename T>
Maillon<T> *Maillon<T>::getSuivant() const
{
    return suivant;
}

template <typename T>
void Maillon<T>::Afficher() const
{
    valeur->Afficher();
}

template <typename T>
void Maillon<T>::ModifierValeur(T *nouvelleValeur)
{
    valeur = nouvelleValeur;
}

#endif // MAILLON_H