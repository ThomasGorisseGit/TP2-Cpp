#include <iostream>
#include <cstring>
using namespace std;
#include "TrajetSimple.h"
#include "Trajet.h"
#include <cstring>

// Couleurs pour l'affichage
#define DEBUT_BOLD_GREEN "\033[1;32m"
#define BOLD_WHITE "\033[1m"
#define FIN "\033[0m"

void TrajetSimple::Afficher() const
{
    cout << "Trajet partant de " << DEBUT_BOLD_GREEN << depart << FIN << " allant à " << DEBUT_BOLD_GREEN << arrivee << FIN
         << " en " << BOLD_WHITE << transport << FIN << endl;
}

void TrajetSimple::AfficherPetit() const
{
    cout << DEBUT_BOLD_GREEN << depart << FIN << " à " << DEBUT_BOLD_GREEN << arrivee << FIN << " en " << BOLD_WHITE << transport << FIN;
}

TrajetSimple::TrajetSimple(const char *Depart, const char *Arrivee, char *M_transport) : Trajet(Depart, Arrivee)
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
    transport = new char[strlen(M_transport) + 1];
    strcpy(transport, M_transport);
}

TrajetSimple::TrajetSimple(const Trajet &ref, char *trans) : Trajet(ref)
{
#ifdef MAP
    cout << "Appel au constructeur de copie2 de <TrajetSimple>" << endl;
#endif
    this->transport = new char[strlen(trans) + 1];
    strcpy(this->transport, trans);
}

TrajetSimple::~TrajetSimple()
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
    delete[] transport;
}
