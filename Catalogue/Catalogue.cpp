#include <iostream>

#include <cstring>
#include "Catalogue.h"
#include "../Trajet/Trajet.h"
#include "../Liste/Liste.h"
using namespace std;

Catalogue::Catalogue(const Catalogue &unCatalogue)
// Constructeur de copie d'un catalogue
// Réalise une copie en profondeur 
// Algorithme : 
//      Parcours la liste des trajets d'un catalogue donné en paramètre,
//      et les ajoute a la liste des trajets courrants.
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
// Constructeur par défaut.
// Initialise la liste des trajets avec une liste vide.
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
    this->listeTrajet = new Liste<Trajet>;
} //----- Fin de Catalogue (Constructeur par défaut)

Catalogue::~Catalogue()
// Déstructeur de catalogue.
// Appel le destructeur de la liste.
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
    delete listeTrajet;
} //----- Fin de ~Catalogue (Destructeur de catalogue)

void Catalogue::Ajouter(Trajet *trajet)
// Méthode d'ajout d'un trajet à la liste courante.
// Algorithme : 
//      Récupère le pointeur de trajet passé en paramètre et l'ajoute a la liste des trajets courant
//      Grâce à la méthode ajouter de Liste
{
    this->listeTrajet->Ajouter(trajet);
} // Fin de la méthode ajouter

void Catalogue::Afficher()
// Méthode permettant d'afficher de manière sophistiquée (!= de brute) le contenu du catalogue.
// Algorithme : 
//      Parcours la liste des trajets courants et appel de la méthode afficher de trajet.
//      <!> Interdiction de surcharger l'opérateur '<<' <!>

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
}// Fin de la méthode afficher

void Catalogue::Rechercher(const char *depart, const char *arrivee, Liste<Trajet> &listeARemplir) const
// Méthode de recherche simple qui trouvent des trajets ayant un départ et une arrivée égale aux constante données en paramètres.
// Le retour de la méthode se fait dans la listeARemplir.
// Algorithme : 
//      Parcours de la liste des trajets et comparaison des chaînes de caractère pour déterminer lesquels sont égales.
//      On ajoute a la liste à remplir les trajets qui coincides avec les paramètres.
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
}// Fin de la méthode de recherche de trajets


void Catalogue::RechercheAvancee(const char *depart, const char *arrivee)
// Méthode permettant la recherche avancee de trajets en combinant les arrivées et les départs afin de proposer un itinéraire optimal.
// Algorithme :
//
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
