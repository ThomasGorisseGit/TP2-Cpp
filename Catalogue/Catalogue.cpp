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
        if(strcmp(listeTrajet->GetValeur(i)->GetDepart(), Depart) == 0 && strcmp(listeTrajet->GetValeur(i)->GetArrivee(), Arrivee) == 0)
        {
            ListeARemplir.Ajouter(listeTrajet->GetValeur(i));
        }
        
    }

}


// Fonction de recherche de trajet
void RechercherTrajet(const char * depart, const char * arrivee) {
    cout << "Recherche de trajet de " << depart << " à " << arrivee << " :\n";
}
    
void Catalogue::initSearch(const char * depart,const char * arrivee){
    
    Liste<Trajet> * listeTrajetParcourus = RechercheDepuisDepart(depart);
    Liste<Trajet> * listeARemplir = new Liste<Trajet>;
    
    //TODO : Split trajet compose en trajet simple
    
    this->TrajetArrivantADestination(listeTrajetParcourus, arrivee, listeARemplir);

    //Reverse listeARemplir : 
    Liste<Trajet> * listeARemplirReverse = new Liste<Trajet>;
    unsigned int taille = listeARemplir->GetTaille();
    for (unsigned int i = 0; i < taille; i ++)
    {
        listeARemplirReverse->Ajouter(listeARemplir->GetValeur(taille-i-1));
    }
    this->Afficherl(listeARemplirReverse);
    // TODO : delete listeARemplirReverse
    // TODO : delete listeARemplir
    // TODO : delete listeTrajetParcourus
    /*
        delete listeARemplirReverse;
        delete listeARemplir;
        delete listeTrajetParcourus;
    */

}
bool Catalogue::TrajetArrivantADestination(Liste<Trajet> * listeTrajetParcourus, const char * arrivee,Liste<Trajet> * listeARemplir){
    unsigned int taille = listeTrajetParcourus->GetTaille();
    for (unsigned int i = 0; i < taille; i ++)
    {
        if (strcmp(listeTrajetParcourus->GetValeur(i)->GetArrivee(), arrivee) == 0 )
        {
            listeARemplir->Ajouter(listeTrajetParcourus->GetValeur(i));
            //cout << listeTrajetParcourus->GetValeur(i)->GetDepart() << " -> " << listeTrajetParcourus->GetValeur(i)->GetArrivee() << endl;
            //cout << "--------------------"<<endl;
            return true;
        }else{
            Liste<Trajet> * listeTrajetParcourus2 = RechercheDepuisDepart(listeTrajetParcourus->GetValeur(i)->GetArrivee());
            if (TrajetArrivantADestination(listeTrajetParcourus2, arrivee, listeARemplir))
            {
                listeARemplir->Ajouter(listeTrajetParcourus->GetValeur(i));
                //cout << listeTrajetParcourus->GetValeur(i)->GetDepart() << " -> " << listeTrajetParcourus->GetValeur(i)->GetArrivee() << endl;

            }
        }
    }
    return false;
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

