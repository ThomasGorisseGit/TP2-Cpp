#include <iostream>
#include <cstring>
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
void Catalogue::Afficherl(Liste <Trajet> * liste)
{
    unsigned int i = 0;
    while (i < liste->GetTaille())
    {
        liste->GetValeur(i)->Afficher();
        i++;
    }
}

void  Catalogue::Rechercher(const char* Depart, const char* Arrivee, Liste<Trajet> & ListeARemplir) const
{
    unsigned int taille = listeTrajet->GetTaille();
    for (unsigned int i = 0; i < taille-1; i ++)
    {
        //TODO : Tester et voir si le egal marche comparé aux strcmp
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
        if (strcmp(listeTrajet->GetValeur(i)->GetDepart(), depart) == 0 )
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
    
void Catalogue::initSearch(const char * depart,const char * arrivee){
    
    Liste<Trajet> * maliste = RechercheDepuisDepart(depart);
    parse(maliste,arrivee);
}
void Catalogue::parse(Liste<Trajet> * l, const char * arrivee){
    //TODO : 
    // Le systeme de recherche trouve s'il est possible de faire un trajet
    // Il faut desormais stocker tous les trajets possibles dans une liste
    // et les afficher
    for (unsigned int i =0;i<l->GetTaille();i++){

        if (strcmp(l->GetValeur(i)->GetArrivee(),arrivee) == 0){
            l->GetValeur(i)->Afficher();
        }
        else{
            l = RechercheDepuisDepart(l->GetValeur(i)->GetArrivee());
            parse(l,arrivee);
        }
    }
}

