#include <iostream>
#include "Catalogue.h"
#include "../Trajet/Trajet.h"
#include "../Liste/Liste.h"
using namespace std;

Catalogue::Catalogue(const Catalogue &unCatalogue)
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Catalogue>" << endl;
#endif
    this->listeTrajet = new Liste<Trajet>;

    for (unsigned int i = 0; i < unCatalogue.listeTrajet->GetTaille(); i++)
    {
        this->listeTrajet->Ajouter(
            *(unCatalogue.listeTrajet->GetValeur(i)));
    }
} //----- Fin de Catalogue (constructeur de copie)

Catalogue::Catalogue()
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
    this->listeTrajet = new Liste<Trajet>;
} //----- Fin de Catalogue

Catalogue::~Catalogue()
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
} //----- Fin de ~Catalogue

void Catalogue::Ajouter(const Trajet &trajet)
{
    this->listeTrajet->Ajouter(trajet);
}

void Catalogue::Afficher()
{

    cout << "-----------------------------------------------------------------" << endl;
    cout << "---------------------------BIENVENUE-----------------------------" << endl;
    cout << "---------------------------SUR    LE-----------------------------" << endl;
    cout << "---------------------------CATALOGUE-----------------------------" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    unsigned int i = 0;
    while (i < this->listeTrajet->GetTaille())
    {
        this->listeTrajet->GetValeur(i)->Afficher();
    }
}

void  Catalogue::Rechercher(const char* Depart, const char* Arrivee, Liste<Trajet> & ListeARemplir) const
{
    int taille = listeTrajet->GetTaille();
    for (unsigned int i = 0; i < taille-1; i ++)
    {
        if(listeTrajet->GetValeur(i)->GetDepart() == Depart && listeTrajet->GetValeur(i)->GetArrivee() == Arrivee)
        {
            ListeARemplir.Ajouter(*listeTrajet->GetValeur(i));
        }
    }

}

// Fonction de recherche de trajet
void RechercherTrajet(const char * depart, const char * arrivee) {
    cout << "Recherche de trajet de " << depart << " à " << arrivee << " :\n";

    
    


}

