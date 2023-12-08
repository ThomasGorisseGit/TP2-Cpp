#include <iostream>
using namespace std;
#include <cstring>
#include "TrajetCompose.h"
#include "TrajetSimple.h"
#include "Trajet.h"
#include "../Liste/Liste.h"

void TrajetCompose::Afficher() const
{
    cout << "Affiche du compose" << endl;
    for (unsigned int i = 0; i < *taille; i++)
    {
        listeTrajetCompose->GetValeur(i)->AfficherPetit();
        cout << "Affichage composé" << endl;
    }
}

TrajetCompose::TrajetCompose(Liste<TrajetSimple> listeTrajetSimple) : Trajet(listeTrajetSimple.GetValeur(0)->GetDepart(), listeTrajetSimple.GetValeur(listeTrajetSimple.GetTaille() - 1)->GetArrivee())
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
    taille = new unsigned int;               // On alloue la mémoire pour la taille
    *taille = listeTrajetSimple.GetTaille(); // On récupère la taille de la liste de trajet simple

    this->listeTrajetCompose = new Liste<TrajetSimple>; // On alloue la mémoire pour la liste de trajet simple

    for (unsigned int i = 0; i < *taille; i++)
    {
        listeTrajetCompose->Ajouter(listeTrajetSimple.GetValeur(i));
    }
}

TrajetCompose::~TrajetCompose()
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
    delete taille;
    delete listeTrajetCompose;
}
