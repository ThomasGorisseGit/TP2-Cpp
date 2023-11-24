#include <iostream>
using namespace std;
#include "TrajetSimple.h"




TrajetSimple::Ajouter

TrajetSimple::TrajetSimple (const char * Depart, const char * Arrivee ) DepartVille(Depart), ArriveeVille(Arrivee)
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
} 


TrajetSimple::~TrajetSimple ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
}

