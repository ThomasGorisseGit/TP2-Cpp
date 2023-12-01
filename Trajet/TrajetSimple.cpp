#include <iostream>
using namespace std;
#include "TrajetSimple.h"
#include "Trajet.h"

// TrajetSimple::Ajouter

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
