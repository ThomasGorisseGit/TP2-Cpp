#include <iostream>
using namespace std;
#include <cstring>
#include "TrajetCompose.h"
#include "TrajetSimple.h"
#include "Trajet.h"
#include "../Liste/Liste.h"



void TrajetCompose::Afficher() const
{
    for(unsigned int i; i < taille; i++)
    {
        ListeTrajetCompose.GetValeur(i)->AfficherPetit();
    }
}

TrajetCompose::TrajetCompose(const Liste<TrajetSimple> & listeTrajetSimple) : Trajet(listeTrajetSimple.GetValeur(0)->GetDepart(), listeTrajetSimple.GetValeur(listeTrajetSimple.GetTaille() - 1)->GetArrivee()),
ListeTrajetCompose(listeTrajetSimple)
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
    taille = listeTrajetSimple.GetTaille();
    // création d'un objet Trajet
}

TrajetCompose::~TrajetCompose()
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
}
