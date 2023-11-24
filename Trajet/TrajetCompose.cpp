#include <iostream>
using namespace std;
#include <cstring>
#include "TrajetCompose.h"



void TrajetCompose::Ajouter (const Trajet &trajet) {
    this->ListeTrajetCompose.ajouter(trajet);
}

void TrajetCompose::Afficher()
{

}

TrajetCompose::TrajetCompose (Liste<TrajetSimple> listeTrajetSimple): 
    Trajet(listeTrajetSimple.GetValeur(0).depart,listeTrajetSimple.GetValeur(listeTrajetSimple.GetTaille()-1).arrivee)
{
    #ifdef MAP
        cout << "Appel au constructeur de <TrajetCompose>" << endl;
    #endif
    int taille = listeTrajetSimple.GetTaille();
    for (int i = 0; i < taille; i++) 
    { 
        //ajoute éléments par éléments les trajets de la liste en paramètre
        ListeTrajetComposee.Ajouter(listeTrajetSimple.GetValeur(i));
    }
    //création d'un objet Trajet
    
} 


TrajetCompose::~TrajetCompose ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
}   
