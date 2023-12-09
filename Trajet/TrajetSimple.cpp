#include <iostream>
#include <cstring>
using namespace std;
#include "TrajetSimple.h"
#include "Trajet.h"
#include <cstring>

// Couleurs pour l'affichage
#define DEBUT_BACKGROUND_GREEN "\033[42m"
#define FIN_BACKGROUND_GREEN "\033[0m"
#define BOLD_WHITE "\033[1m"
#define FIN_BOLD_WHITE "\033[0m"

// TrajetSimple::Afficher

char *TrajetSimple::GetTransport() const
{
    return transport;
}

void TrajetSimple::Afficher() const
{
    cout << "Trajet partant de " << DEBUT_BACKGROUND_GREEN << depart << FIN_BACKGROUND_GREEN << " allant à " << DEBUT_BACKGROUND_GREEN << arrivee << FIN_BACKGROUND_GREEN
         << " en " << BOLD_WHITE << transport << FIN_BOLD_WHITE << endl;
}

void TrajetSimple::AfficherPetit() const
{
    cout << DEBUT_BACKGROUND_GREEN << depart << FIN_BACKGROUND_GREEN << " à " << DEBUT_BACKGROUND_GREEN << arrivee << FIN_BACKGROUND_GREEN << " en " << BOLD_WHITE << transport << FIN_BOLD_WHITE;
}

TrajetSimple::TrajetSimple(const char *Depart, const char *Arrivee, char *M_transport) : Trajet(Depart, Arrivee)
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
    transport = new char[strlen(M_transport) + 1];
    strcpy(transport, M_transport);
}
TrajetSimple::TrajetSimple(const TrajetSimple &ref) : Trajet(ref)
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <TrajetSimple>" << endl;
#endif
    this->transport = new char[strlen(ref.transport) + 1];
    strcpy(this->transport, ref.transport);
}

TrajetSimple::TrajetSimple(const Trajet &ref, char *trans) : Trajet(ref)
{
#ifdef MAP
    cout << "Appel au constructeur de copie2 de <TrajetSimple>" << endl;
#endif
    this->transport = new char[strlen(trans) + 1];
    strcpy(this->transport, trans);
}

int TrajetSimple::GetType() const
{
    return Simple; // enum = 0
}

unsigned int TrajetSimple::GetTailleTrajet() const
{
    return 1; // taille d'un trajet simple par défaut
}

TrajetSimple::~TrajetSimple()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
    delete[] transport;
}
