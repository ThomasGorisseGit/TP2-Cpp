#include <iostream>
using namespace std;
#include "TrajetSimple.h"
#include "Trajet.h"

// TrajetSimple::Afficher

void TrajetSimple::Afficher() const
{
    cout << "Trajet partant de " << depart << " allant à  " << arrivee << "en" << transport << endl;
}

void TrajetSimple::AfficherPetit() const
{
    cout << depart << " -> " << arrivee << " en " << transport << endl;
}

TrajetSimple::TrajetSimple(char *Depart, char *Arrivee,char * M_transport) : Trajet(Depart, Arrivee), transport(M_transport)
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
}

TrajetSimple::~TrajetSimple()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
}
