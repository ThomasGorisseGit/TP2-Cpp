#include <iostream>
using namespace std;
#include <cstring>
#include "TrajetCompose.h"
#include "TrajetSimple.h"
#include "Trajet.h"
#include "../Liste/Liste.h"

#define DEBUT_MAGENTA "\033[35m"
#define FIN "\033[0m"

void TrajetCompose::Afficher() const
{

    for (unsigned int i = 0; i < *taille; i++)
    {
        listeTrajetCompose->GetValeur(i)->AfficherPetit();
        // si ce n'est pas le dernier trajet simple
        if (i < *taille - 1)
            cout << DEBUT_MAGENTA << " ➔ " << FIN;
        else
            cout << endl;
    }
}

TrajetCompose::TrajetCompose(Liste<TrajetSimple> &listeTrajetSimple) : Trajet(listeTrajetSimple.GetValeur(0)->GetDepart(),
                                                                              listeTrajetSimple.GetValeur(listeTrajetSimple.GetTaille() - 1)->GetArrivee())
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
    taille = new unsigned int;
    *taille = listeTrajetSimple.GetTaille(); // On récupère la taille de la liste de trajet simple

    this->listeTrajetCompose = new Liste<TrajetSimple>;

    for (unsigned int i = 0; i < *taille; i++)
    {
        TrajetSimple *trajetSimpleTMP = new TrajetSimple(*listeTrajetSimple.GetValeur(i),
                                                         listeTrajetSimple.GetValeur(i)->GetTransport());
        listeTrajetCompose->Ajouter(trajetSimpleTMP);
    }
}

void TrajetCompose::Decompose(Liste<TrajetSimple> &listeTrajetSimple)
{

    for (unsigned int i = 0; i < *taille; i++)
    {
        // Ajoute tous les trajets simples à la liste donnée en paramètre
        listeTrajetSimple.Ajouter(listeTrajetCompose->GetValeur(i));
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
