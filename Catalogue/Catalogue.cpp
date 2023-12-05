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
            unCatalogue.listeTrajet->GetValeur(i));
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
    delete listeTrajet;
} //----- Fin de ~Catalogue

void Catalogue::Ajouter(Trajet *trajet)
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

void Catalogue::Rechercher(const char *depart, const char *arrivee, Liste<Trajet> &listeARemplir) const
{
    unsigned int taille = listeTrajet->GetTaille();
    for (unsigned int i = 0; i < taille - 1; i++)
    {
        // TODO : Tester et voir si le egal marche comparé aux strcmp
        if (strcmp(listeTrajet->GetValeur(i)->GetDepart(), depart) == 0 && strcmp(listeTrajet->GetValeur(i)->GetArrivee(), arrivee) == 0)
        {
            listeARemplir.Ajouter(listeTrajet->GetValeur(i));
        }
    }
}

// Fonction de recherche de trajet


void Catalogue::RechercheAvancee(const char *depart, const char *arrivee)
{

    Liste<Trajet> *listeTrajetParcourus = rechercheDepuisDepart(depart);
    Liste<Trajet> *listeARemplir = new Liste<Trajet>;

    // TODO : Split trajet compose en trajet simple

    this->trajetArrivantADestination(listeTrajetParcourus, arrivee, listeARemplir);

    // Reverse listeARemplir :
    Liste<Trajet> *listeARemplirReverse = new Liste<Trajet>;
    unsigned int taille = listeARemplir->GetTaille();
    for (unsigned int i = 0; i < taille; i++)
    {
        listeARemplirReverse->Ajouter(listeARemplir->GetValeur(taille - i - 1));
    }
    unsigned int i = 0;
    while (i < listeARemplirReverse->GetTaille())
    {
        listeARemplirReverse->GetValeur(i)->Afficher();
        i++;
    }
    // TODO : delete listeARemplirReverse
    // TODO : delete listeARemplir
    // TODO : delete listeTrajetParcourus
}

bool Catalogue::trajetArrivantADestination(Liste<Trajet> *listeTrajetParcourus, const char *arrivee, Liste<Trajet> *listeARemplir)
{
    unsigned int taille = listeTrajetParcourus->GetTaille();
    for (unsigned int i = 0; i < taille; i++)
    {
        if (strcmp(listeTrajetParcourus->GetValeur(i)->GetArrivee(), arrivee) == 0)
        {
            listeARemplir->Ajouter(listeTrajetParcourus->GetValeur(i));
            // cout << listeTrajetParcourus->GetValeur(i)->GetDepart() << " -> " << listeTrajetParcourus->GetValeur(i)->GetArrivee() << endl;
            // cout << "--------------------"<<endl;
            return true;
        }
        else
        {
            Liste<Trajet> *listeTrajetParcourus2 = rechercheDepuisDepart(listeTrajetParcourus->GetValeur(i)->GetArrivee());
            if (trajetArrivantADestination(listeTrajetParcourus2, arrivee, listeARemplir))
            {
                listeARemplir->Ajouter(listeTrajetParcourus->GetValeur(i));
                // cout << listeTrajetParcourus->GetValeur(i)->GetDepart() << " -> " << listeTrajetParcourus->GetValeur(i)->GetArrivee() << endl;
            }
        }
    }
    return false;
}
Liste<Trajet> *Catalogue::rechercheDepuisDepart(const char *depart)
{
    Liste<Trajet> *listeARemplir = new Liste<Trajet>;
    unsigned int taille = listeTrajet->GetTaille();
    for (unsigned int i = 0; i < taille; i++)
    {
        if (strcmp(listeTrajet->GetValeur(i)->GetDepart(), depart) == 0)
        {
            listeARemplir->Ajouter(listeTrajet->GetValeur(i));
        }
    }
    return listeARemplir;
}
