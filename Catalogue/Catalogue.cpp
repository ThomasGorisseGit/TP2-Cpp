#include <iostream>

#include <cstring>
#include "Catalogue.h"
#include "../Trajet/Trajet.h"
#include "../Liste/Liste.h"
using namespace std;

// Couleur pour l'affichage
#define BOLD_WHITE "\033[1m"
#define FIN "\033[0m"
#define DEBUT_BACKGROUND_GREEN "\033[42m"

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
    this->listeTrajetEnSimple = new Liste<TrajetSimple>;
} //----- Fin de Catalogue (Constructeur par défaut)

Catalogue::~Catalogue()
// Déstructeur de catalogue.
// Appel le destructeur de la liste.
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
    delete listeTrajet;
    delete listeTrajetEnSimple;
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

    cout << BOLD_WHITE << "-----------------------------------------------------------------" << FIN << endl;
    cout << BOLD_WHITE << "---------------------------" << DEBUT_BACKGROUND_GREEN << "BIENVENUE" << FIN << BOLD_WHITE << "-----------------------------" << FIN << endl;
    cout << BOLD_WHITE << "---------------------------" << DEBUT_BACKGROUND_GREEN << "SUR" << FIN << "    " << DEBUT_BACKGROUND_GREEN << BOLD_WHITE << "LE" << FIN << BOLD_WHITE << "-----------------------------" << FIN << endl;
    cout << BOLD_WHITE << "---------------------------" << DEBUT_BACKGROUND_GREEN << "CATALOGUE" << FIN << BOLD_WHITE << "-----------------------------" << FIN << endl;
    cout << BOLD_WHITE << "-----------------------------------------------------------------" << FIN << endl
         << endl;

    if (this->listeTrajet->GetTaille() == 0)
    {
        cout << BOLD_WHITE << "Le catalogue est vide" << FIN << endl;
        return;
    }

    if (listeTrajetSimple->GetTaille() != 0)
    {
        cout << BOLD_WHITE << "Voici la liste des trajets simples :" << FIN << endl;
        listeTrajetSimple->Afficher();
        cout << endl;
    }
    else
    {
        cout << BOLD_WHITE << "Il n'y a pas de trajets simples dans le catalogue" << FIN << endl;
    }

    if (listeTrajetCompose->GetTaille() != 0)
    {
        cout << BOLD_WHITE << "Voici la liste des trajets composés :" << FIN << endl;
        listeTrajetCompose->Afficher();
        cout << endl;
    }
    else
    {
        cout << BOLD_WHITE << "Il n'y a pas de trajets composés dans le catalogue" << FIN << endl;
    }

} // Fin de la méthode afficher

Liste<TrajetSimple> * Catalogue::Rechercher(const char *depart, const char *arrivee, bool verbose) const
// Méthode de recherche simple qui trouvent des trajets ayant un départ et une arrivée égale aux constante données en paramètres.
// Le retour de la méthode se fait dans la listeARemplir.
// Algorithme :
//      Parcours de la liste des trajets et comparaison des chaînes de caractère pour déterminer lesquels sont égales.
//      On ajoute a la liste à remplir les trajets qui coincides avec les paramètres.
{   
    Liste<TrajetSimple> * listeChemins = new Liste<TrajetSimple>;
    unsigned int cptTrajet = 0;
    // cout << "1 : " << listeTrajet->GetValeur(0)->GetDepart()  <<" Taille "<<  listeTrajet->GetTaille() <<endl;
    unsigned int taille = listeTrajet->GetTaille();
    for (unsigned int i = 0; i < taille; i++)
    {

        if (listeTrajet->GetValeur(i)->GetType() == 1) // est un trajet simple
            {
                if (strcmp(listeTrajet->GetValeur(i)->GetDepart(), depart) == 0 && strcmp(listeTrajet->GetValeur(i)->GetArrivee(), arrivee) == 0)
                {
                    if (verbose) listeTrajet->GetValeur(i)->Afficher();
                    cptTrajet++;
                    TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i), listeTrajet->GetValeur(i)->GetTransport());
                    listeChemins->Ajouter(TrajetSimpleRemplissage);
                }
            }

        else
        {
            // Si on tombe sur un trajet compose, on ajoute tous les trajets simples
            // compris dans ce trajet composé
            unsigned int tailleTrajetCompose = listeTrajet->GetValeur(i)->GetTailleTrajet();
            for (unsigned int j = 0; j < tailleTrajetCompose; j++)
            {
                if (strcmp(listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetDepart(), depart) == 0 && strcmp(listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetArrivee(), arrivee) == 0)
            {
                if (verbose) listeTrajet->GetValeur(i)->GetTrajetSimple(j)->Afficher();
                TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i)->GetTrajetSimple(j), listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetTransport());
                listeChemins->Ajouter(TrajetSimpleRemplissage);
                cptTrajet++;

            }
            }
            
        }
    }
    if (!cptTrajet && verbose)
    {
        cout << "Pas de trajet correspondant trouvé parmis les "<< taille << " trajets." << endl;
    }
    return listeChemins;

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
    unsigned tailledebug = listeTrajetParcourus->GetTaille();
    cout << "Taille finale : " << tailledebug << endl;
    listeTrajetParcourus->Afficher();
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
                
                
                unsigned int tailleTrajetCompose = listeTrajet->GetValeur(i)->GetTailleTrajet();
                cout << "Utilise un trajet Composes de taille " << tailleTrajetCompose << endl;
                for (unsigned int j = 0; j < tailleTrajetCompose; j++)
                {
                    TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i)->GetTrajetSimple(j), listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetTransport());
                    listeARemplir->Ajouter(TrajetSimpleRemplissage);
                    cout << "Ajoute i : " << i << " j : " << j << endl;
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


void Catalogue::Simplification()
{
    delete listeTrajetEnSimple;
    listeTrajetEnSimple = new Liste<TrajetSimple>;
    unsigned int taille = listeTrajet->GetTaille();
    for (unsigned int i = 0; i < taille; i++)
    {
            
            if (listeTrajet->GetValeur(i)->GetType() == 1) // est un trajet simple
            {
                TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i), listeTrajet->GetValeur(i)->GetTransport());
                listeTrajetEnSimple->Ajouter(TrajetSimpleRemplissage);
                
            }

            else
            {
                // Si on tombe sur un trajet compose, on ajoute tous les trajets simples
                // compris dans ce trajet composé
                
                unsigned int tailleTrajetCompose = listeTrajet->GetValeur(i)->GetTailleTrajet();
                for (unsigned int j = 0; j < tailleTrajetCompose; j++)
                {
                    TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i)->GetTrajetSimple(j), listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetTransport());
                    listeTrajetEnSimple->Ajouter(TrajetSimpleRemplissage);
                   
                }
                
            }
        
    }
}

// Fonction récursive de recherche d'itinéraires entre deux points
void Catalogue::RechercheAvanceeGabin(const char *depart, const char *arrivee, Liste<TrajetSimple> & itineraires, Liste<TrajetSimple> & itineraireActuel)
{
    
    //listeTrajetEnSimple->Afficher();
    cout << "Recherche d'un trajet partant de : " << depart << " à " << arrivee << endl;
    
    // Si la liste d'itinéraires actuelle atteint la destination, l'ajouter à la liste complète d'itinéraires
    if (itineraireActuel.GetTaille() > 0 && strcmp(itineraireActuel.GetValeur(itineraireActuel.GetTaille() - 1)->GetArrivee(),arrivee) == 0)
    {
        itineraires.Ajouter(&itineraireActuel);
        cout << "FIN";
        return;
    }

    // Recherche récursive des itinéraires possibles à partir du dernier point de l'itinéraire actuel
    Trajet* dernierTrajet = itineraireActuel.GetTaille() > 0 ? itineraireActuel.GetValeur(itineraireActuel.GetTaille() - 1) : nullptr;

    for (unsigned int i = 0; i < listeTrajetEnSimple->GetTaille(); ++i)
    {
        
        TrajetSimple * trajet = listeTrajetEnSimple->GetValeur(i);
        
        // Vérifier si le départ du trajet correspond au dernier point de l'itinéraire actuel
        cout << "Test boucle"  << endl;
        cout << trajet->GetDepart() << endl;
        if (strcmp(trajet->GetDepart(),(dernierTrajet ? dernierTrajet->GetArrivee() : depart)) == 0) //compare à l'arrivée du dernier trajet, si il existe, sinon au depart de la recherche
        {
            if (!dernierTrajet) cout << "Premier" <<endl;
            // Éviter les boucles infinies en vérifiant si le trajet n'a pas déjà été inclus dans l'itinéraire actuel
            if (itineraireActuel.Rechercher(trajet) == 0)
            {
                // Ajouter le trajet à l'itinéraire actuel
                //TrajetSimple * TrajetAjout = new TrajetSimple(trajet);
                cout << "Ajout " << endl;
                itineraireActuel.Ajouter(trajet);

                // Recherche récursive pour l'itinéraire suivant
                
                RechercheAvanceeGabin(depart, arrivee, itineraires, itineraireActuel);

                // Retirer le trajet de l'itinéraire actuel pour explorer d'autres possibilités
                //itineraireActuel.Erase(itineraireActuel.GetTaille() - 1);
            }
            else cout << "Boucle de Trajet" << endl;
            //delete trajet;
        }
        else 
        {
            cout << "Pas le bon" << endl;
            trajet->Afficher();
            //delete trajet;
        }
        
        
    }
    cout << "Fin non conventionnelle" << endl;
}

