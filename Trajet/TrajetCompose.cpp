#include <iostream>
using namespace std;
#include <cstring>
#include "TrajetCompose.h"



void TrajetCompose::Ajouter (const Trajet &trajet) {
    this->ListeTrajetCompose.ajouter(trajet);
}

TrajetCompose::TrajetCompose (const char * Depart, const char * Arrivee ): 
{
    
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
} 


TrajetCompose::~TrajetCompose ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
}   
