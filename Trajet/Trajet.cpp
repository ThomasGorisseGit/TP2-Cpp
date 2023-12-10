#include <iostream>
#include <cstring>
using namespace std;

#include "Trajet.h"

Trajet::Trajet(const char *DepartVille, const char *ArriveeVille)
{
#ifdef MAP
    cout << "Appel au constructeur de <Trajet>" << endl;
#endif

    depart = new char[strlen(DepartVille) + 1];
    strcpy(depart, DepartVille);

    arrivee = new char[strlen(ArriveeVille) + 1];
    strcpy(arrivee, ArriveeVille);
}

Trajet::Trajet(const Trajet &ref)
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Trajet>" << endl;
#endif
    this->depart = new char[strlen(ref.depart) + 1];
    this->arrivee = new char[strlen(ref.arrivee) + 1];
    strcpy(this->depart, ref.depart);
    strcpy(this->arrivee, ref.arrivee);
}

Trajet::~Trajet()
{
#ifdef MAP
    cout << "Appel au destructeur de <Trajet> ";
    cout << "Destruction de " << depart << " et " << arrivee << endl;
#endif
    delete[] depart;
    delete[] arrivee;
}