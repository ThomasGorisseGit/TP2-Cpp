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
    if (this->listeTrajet->GetTaille() == 0)
    {
        cout << "Le catalogue est vide" << endl;
    }

    while (i < this->listeTrajet->GetTaille())
    {
        this->listeTrajet->GetValeur(i)->Afficher();
        i++;
    }
} // Fin de la méthode afficher

void Catalogue::Rechercher(const char *depart, const char *arrivee) const
// Méthode de recherche simple qui trouvent des trajets ayant un départ et une arrivée égale aux constante données en paramètres.
// Le retour de la méthode se fait dans la listeARemplir.
// Algorithme :
//      Parcours de la liste des trajets et comparaison des chaînes de caractère pour déterminer lesquels sont égales.
//      On ajoute a la liste à remplir les trajets qui coincides avec les paramètres.
{

    unsigned int cptTrajet = 0;
    // cout << "1 : " << listeTrajet->GetValeur(0)->GetDepart()  <<" Taille "<<  listeTrajet->GetTaille() <<endl;
    unsigned int taille = listeTrajet->GetTaille();
    for (unsigned int i = 0; i < taille; i++)
    {

        if (strcmp(listeTrajet->GetValeur(i)->GetDepart(), depart) == 0 && strcmp(listeTrajet->GetValeur(i)->GetArrivee(), arrivee) == 0)
        {
            listeTrajet->GetValeur(i)->Afficher();
            cptTrajet++;
        }
    }
    if (!cptTrajet)
    {
        cout << "Pas de trajet correspondant trouvé" << endl;
    }

} // Fin de la méthode de recherche de trajets

void Catalogue::RechercheAvancee(const char *depart, const char *arrivee)
// Méthode permettant la recherche avancee de trajets en combinant les arrivées et les départs afin de proposer un itinéraire optimal.
// Algorithme :
//      On a une liste des Trajets parcourus, que l'on remplie avec les trajets liés au point de départ.
//      On créé une liste A remplir qui contiendra les différents chemins vers le point d'arrivée.
//      On invoque la méthode trajetArrivantADestination qui remplie la listeARemplir des chemins vers l'arrivée.
//      Puisque cette méthode est récursive, l'ajout dans la liste est à l'envers, on retourne donc listeARemplir pour l'afficher dans le bon sens
{

    Liste<Trajet> *listeTrajetParcourus = new Liste<Trajet>;
    rechercheDepuisDepart(depart, listeTrajetParcourus);
    Liste<Trajet> *listeARemplir = new Liste<Trajet>;

    // TODO : Split trajet compose en trajet simple || ! || STILL UP TO DATE 06/12

    this->trajetArrivantADestination(listeTrajetParcourus, arrivee, listeARemplir);
    // On récupère grâce a cette méthode les trajets qui nous emmèneront jusqu'à l'arrivée

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
    delete listeARemplirReverse;
    delete listeARemplir;
    delete listeTrajetParcourus;
}

bool Catalogue::trajetArrivantADestination(Liste<Trajet> *listeTrajetParcourus, const char *arrivee, Liste<Trajet> *listeARemplir)
// Méthode permettant de trouver la liste des trajets qui emmène jusqu'à l'arrivée.
// Algorithme :
//      Elle est utilisée de manière récursive afin de parcourir tous les trajets et de renvoyer ceux qui emmène jusqu'à l'arrivée
//      On passe donc listeTrajetParcourus en paramètre qui stockera tous les trajets effectués afin de ne pas les refaire plusieurs fois
//      On récupère le point d'arrivée
//      Ainsi qu'une listeARemplir qui contiendra le résultat des chemins à prendre qui emmène jusqu'à l'arrivée.
{
    unsigned int taille = listeTrajetParcourus->GetTaille();
    // On parcours tous les trajets parcourus
    for (unsigned int i = 0; i < taille; i++)
    {
        // Si c'est l'arrivée, alors on a trouvé une solution et on l'ajoute dans la liste.
        if (strcmp(listeTrajetParcourus->GetValeur(i)->GetArrivee(), arrivee) == 0)
        {
            listeARemplir->Ajouter(listeTrajetParcourus->GetValeur(i));
            // Puisqu'on l'a trouvée, on renvoie true pour permettre aux if en dessous de propager le résultat et donc d'ajouter les trajets
            // Qui nous ont permis d'arriver jusqu'au résultat.
            return true;
        }
        else
        {
            Liste<Trajet> *listeTrajetParcourus2 = new Liste<Trajet>;
            rechercheDepuisDepart(listeTrajetParcourus->GetValeur(i)->GetArrivee(), listeTrajetParcourus2);
            if (trajetArrivantADestination(listeTrajetParcourus2, arrivee, listeARemplir))
            {
                listeARemplir->Ajouter(listeTrajetParcourus->GetValeur(i));
                // cout << listeTrajetParcourus->GetValeur(i)->GetDepart() << " -> " << listeTrajetParcourus->GetValeur(i)->GetArrivee() << endl;
            }
            delete listeTrajetParcourus2;
        }
    }
    return false;
}
Liste<Trajet> *Catalogue::rechercheDepuisDepart(const char *depart, Liste<Trajet> *listeARemplir)
{
    // Liste<Trajet> *listeARemplir = new Liste<Trajet>;
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
