#include <iostream>
using namespace std;
#include "TrajetSimple.h"
#include "Trajet.h"
#include <cstring>

// TrajetSimple::Afficher

void TrajetSimple::Afficher() const
{
    cout << "Trajet partant de " << depart << " allant à  " << arrivee << "en" << transport << endl;
}

void TrajetSimple::AfficherPetit() const
{
    cout << depart << " -> " << arrivee << " en " << transport << endl;
}

TrajetSimple::TrajetSimple(const char *Depart,const char *Arrivee,const char * M_transport) : Trajet(Depart, Arrivee)
{
    #ifdef MAP
        cout << "Appel au constructeur de <TrajetSimple>" << endl;
    #endif
    transport = new char[sizeof(M_transport)];
    strcpy(transport,M_transport);
}

TrajetSimple::~TrajetSimple()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
}
