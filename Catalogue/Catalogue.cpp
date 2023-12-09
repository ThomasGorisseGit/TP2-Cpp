#include <iostream>

#include <cstring>
#include "Catalogue.h"
#include "../Trajet/Trajet.h"
#include "../Liste/Liste.h"
using namespace std;

// Couleur pour l'affichage
#define BOLD_WHITE "\033[1m"
#define FIN_BOLD_WHITE "\033[0m"

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

void Catalogue::Afficher(Liste<Trajet> *listeTrajetSimple, Liste<Trajet> *listeTrajetCompose) const
// Méthode permettant d'afficher de manière sophistiquée le contenu du catalogue.
// Algorithme :
//      Affiche le catalogue de trajets simples
//      Affiche le catalogue de trajets composés

{

    cout << "-----------------------------------------------------------------" << endl;
    cout << "---------------------------BIENVENUE-----------------------------" << endl;
    cout << "---------------------------SUR    LE-----------------------------" << endl;
    cout << "---------------------------CATALOGUE-----------------------------" << endl;
    cout << "-----------------------------------------------------------------" << endl
         << endl;

    if (this->listeTrajet->GetTaille() == 0)
    {
        cout << BOLD_WHITE << "Le catalogue est vide" << FIN_BOLD_WHITE << endl;
        return;
    }

    if (listeTrajetSimple->GetTaille() != 0)
    {
        cout << BOLD_WHITE << "Voici la liste des trajets simples :" << FIN_BOLD_WHITE << endl;
        listeTrajetSimple->Afficher();
        cout << endl;
    }
    else
    {
        cout << BOLD_WHITE << "Il n'y a pas de trajets simples dans le catalogue" << FIN_BOLD_WHITE << endl;
    }

    if (listeTrajetCompose->GetTaille() != 0)
    {
        cout << BOLD_WHITE << "Voici la liste des trajets composés :" << FIN_BOLD_WHITE << endl;
        listeTrajetCompose->Afficher();
        cout << endl;
    }
    else
    {
        cout << BOLD_WHITE << "Il n'y a pas de trajets composés dans le catalogue" << FIN_BOLD_WHITE << endl;
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

    Liste<TrajetSimple> *listeTrajetParcourus = new Liste<TrajetSimple>;
    rechercheDepuisDepart(depart, listeTrajetParcourus);
    Liste<TrajetSimple> *listeARemplir = new Liste<TrajetSimple>;

    // TODO : Split trajet compose en trajet simple || ! || STILL UP TO DATE 06/12

    this->trajetArrivantADestination(listeTrajetParcourus, arrivee, listeARemplir);
    // On récupère grâce a cette méthode les trajets qui nous emmèneront jusqu'à l'arrivée

    // Reverse listeARemplir :
    Liste<TrajetSimple> *listeARemplirReverse = new Liste<TrajetSimple>;
    unsigned int taille = listeARemplir->GetTaille();
    for (unsigned int i = 0; i < taille; i++)
    {
        TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeARemplir->GetValeur(taille - i - 1), listeARemplir->GetValeur(taille - i - 1)->GetTransport());
        listeARemplirReverse->Ajouter(TrajetSimpleRemplissage);
        // listeARemplirReverse->Ajouter(listeARemplir->GetValeur(taille - i - 1));
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

bool Catalogue::trajetArrivantADestination(Liste<TrajetSimple> *listeTrajetParcourus, const char *arrivee, Liste<TrajetSimple> *listeARemplir)
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
            TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajetParcourus->GetValeur(i), listeTrajetParcourus->GetValeur(i)->GetTransport());
            listeARemplir->Ajouter(TrajetSimpleRemplissage);
            // listeARemplir->Ajouter(listeTrajetParcourus->GetValeur(i));
            //  Puisqu'on l'a trouvée, on renvoie true pour permettre aux if en dessous de propager le résultat et donc d'ajouter les trajets
            //  Qui nous ont permis d'arriver jusqu'au résultat.
            return true;
        }
        else
        {
            Liste<TrajetSimple> *listeTrajetParcourus2 = new Liste<TrajetSimple>;
            rechercheDepuisDepart(listeTrajetParcourus->GetValeur(i)->GetArrivee(), listeTrajetParcourus2);
            if (trajetArrivantADestination(listeTrajetParcourus2, arrivee, listeARemplir))
            {
                // listeARemplir->Ajouter(listeTrajetParcourus->GetValeur(i));
                //  cout << listeTrajetParcourus->GetValeur(i)->GetDepart() << " -> " << listeTrajetParcourus->GetValeur(i)->GetArrivee() << endl;

                TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajetParcourus->GetValeur(i), listeTrajetParcourus->GetValeur(i)->GetTransport());
                listeARemplir->Ajouter(TrajetSimpleRemplissage);
            }
            delete listeTrajetParcourus2;
        }
    }
    return false;
}
Liste<TrajetSimple> *Catalogue::rechercheDepuisDepart(const char *depart, Liste<TrajetSimple> *listeARemplir)
{
    // Liste<Trajet> *listeARemplir = new Liste<Trajet>;
    // Liste<TrajetSimple> *listeMultiSimple
    unsigned int taille = listeTrajet->GetTaille();
    for (unsigned int i = 0; i < taille; i++)
    {
        if (strcmp(listeTrajet->GetValeur(i)->GetDepart(), depart) == 0)
        {

            if (listeTrajet->GetValeur(i)->GetType() == 1) // est un trajet simple
            {
                cout << "Utilise un trajet simple" << endl;
                TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i), listeTrajet->GetValeur(i)->GetTransport());
                listeARemplir->Ajouter(TrajetSimpleRemplissage);
            }

            else
            {
                // Si on tombe sur un trajet compose, on ajoute tous les trajets simples
                // compris dans ce trajet composé
                cout << "Utilise un trajet Composes" << endl;
                unsigned int tailleTrajetCompose = listeTrajet->GetValeur(i)->GetTailleTrajet();
                for (unsigned int j = 0; j < tailleTrajetCompose; j++)
                {
                    TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i)->GetTrajetSimple(j), listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetTransport());
                    listeARemplir->Ajouter(TrajetSimpleRemplissage);
                }
                cout << "Fin du remplissage multiple" << endl;
            }
        }
    }
    return listeARemplir;
}

void Catalogue::GetTrajetSimpleEtCompose(Liste<Trajet> *listeTrajetSimple, Liste<Trajet> *listeTrajetCompose)
{
    unsigned int taille = listeTrajet->GetTaille();
    for (unsigned int i = 0; i < taille; i++)
    {
        if (listeTrajet->GetValeur(i)->GetType() == 1) // est un trajet simple
        {
            listeTrajetSimple->Ajouter(listeTrajet->GetValeur(i));
        }
        else // est un trajet compose
        {
            listeTrajetCompose->Ajouter(listeTrajet->GetValeur(i));
        }
    }
}
