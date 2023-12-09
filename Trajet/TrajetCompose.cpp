#include <iostream>
using namespace std;
#include <cstring>
#include "TrajetCompose.h"
#include "TrajetSimple.h"
#include "Trajet.h"
#include "../Liste/Liste.h"

void TrajetCompose::Afficher() const
{

    for (unsigned int i = 0; i < *taille; i++)
    {
        listeTrajetCompose->GetValeur(i)->AfficherPetit();
        if (i < *taille - 1)
            cout << " puis ";
        else
            cout << endl;
    }
}

TrajetCompose::TrajetCompose(Liste<TrajetSimple> &listeTrajetSimple) : Trajet(listeTrajetSimple.GetValeur(0)->GetDepart(), listeTrajetSimple.GetValeur(listeTrajetSimple.GetTaille() - 1)->GetArrivee())
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
    taille = new unsigned int;               // On alloue la mémoire pour la taille
    *taille = listeTrajetSimple.GetTaille(); // On récupère la taille de la liste de trajet simple

    this->listeTrajetCompose = new Liste<TrajetSimple>; // On alloue la mémoire pour la liste de trajet simple

    for (unsigned int i = 0; i < *taille; i++)
    {
        TrajetSimple *trajetSimpleTMP = new TrajetSimple(*listeTrajetSimple.GetValeur(i));
        listeTrajetCompose->Ajouter(trajetSimpleTMP);
    }
}

void TrajetCompose::Decompose(Liste<TrajetSimple> &listeTrajetSimple)
{

    for (unsigned int i = 0; i < *taille; i++)
    {
        listeTrajetSimple.Ajouter(listeTrajetCompose->GetValeur(i)); // Ajoute tt les trajets simples à la liste donnée
    }
}

unsigned int TrajetCompose::GetTailleTrajet() const
{
    return *taille;
}

Trajet *TrajetCompose::GetTrajetSimple(unsigned int indice) const
{
    return listeTrajetCompose->GetValeur(indice);
}

int TrajetCompose::GetType() const
{
    return Compose; // enum = 1
}

TrajetCompose::~TrajetCompose()
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
    delete taille;
    delete listeTrajetCompose;
}
