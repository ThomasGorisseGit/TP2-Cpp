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
            unCatalogue.listeTrajet->GetValeur(i)
            );
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

void Catalogue::Ajouter(Trajet* trajet)
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
        i++;
    }
}

void  Catalogue::Rechercher(const char* Depart, const char* Arrivee, Liste<Trajet> & ListeARemplir) const
{
    unsigned int taille = listeTrajet->GetTaopille();
    for (unsigned int i = 0; i < taille-1; i ++)
    {
        if(listeTrajet->GetValeur(i)->GetDepart() == Depart && listeTrajet->GetValeur(i)->GetArrivee() == Arrivee)
        {
            ListeARemplir.Ajouter(listeTrajet->GetValeur(i));
        }
    }

}

Liste<Trajet> * Catalogue::RechercheDepuisDepart(const char * depart){
    Liste<Trajet> * listeARemplir = new Liste<Trajet>;
    unsigned int taille = listeTrajet->GetTaille();
    for (unsigned int i = 0; i < taille; i ++)
    {
        if(listeTrajet->GetValeur(i)->GetDepart() == depart)
        {
            listeARemplir->Ajouter(listeTrajet->GetValeur(i));
        }
    }
    return listeARemplir;
}

// Fonction de recherche de trajet
void RechercherTrajet(const char * depart, const char * arrivee) {
    cout << "Recherche de trajet de " << depart << " à " << arrivee << " :\n";
}
    
void Catalogue::initSearch(const char * depart){
    Liste<Trajet> * maliste = RechercheDepuisDepart(depart);
    parse(maliste);

    maliste->Afficher();
}
void Catalogue::parse(Liste<Trajet> * l){
    for (int i =0;i<l->GetTaille();i++){
        if (l->GetValeur(i)->GetArrivee() == arrivee){
            l->GetValeur(i)->Afficher();
        }
        else{
            Liste<Trajet> * l2 = RechercheDepuisDepart(l->GetValeur(i)->GetArrivee());
            parse(l2);
        }
    }
}

