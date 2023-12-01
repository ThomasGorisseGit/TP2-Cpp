#include <iostream>
#include <cstring>
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
TrajetSimple::TrajetSimple( const TrajetSimple& ref) : Trajet(ref) 
{
    #ifdef MAP
        cout << "Appel au constructeur de copie de <TrajetSimple>" << endl;
    #endif
    this->transport = new char[strlen(ref.transport)+1];
    strcpy(this->transport,ref.transport);

}


TrajetSimple::~TrajetSimple()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
}
