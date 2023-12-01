#include <iostream>
using namespace std;
#include <cstring>
#include "TrajetCompose.h"
#include "Trajet.h"
#include "../Liste/Liste.h"

void TrajetCompose::Ajouter(const TrajetSimple &trajet)
{
    ListeTrajetCompose.Ajouter(trajet);
}

void TrajetCompose::Afficher() const
{
}

TrajetCompose::TrajetCompose(const Liste<TrajetSimple> listeTrajetSimple) : Trajet(listeTrajetSimple.GetValeur(0).GetDepart(), listeTrajetSimple.GetValeur(listeTrajetSimple.GetTaille() - 1).GetArrivee())
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
    int taille = listeTrajetSimple.GetTaille();
    for (int i = 0; i < taille; i++)
    {
        // ajoute éléments par éléments les trajets de la liste en paramètre
        ListeTrajetCompose.Ajouter(listeTrajetSimple.GetValeur(i));
    }
    // création d'un objet Trajet
}

TrajetCompose::~TrajetCompose()
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
}
