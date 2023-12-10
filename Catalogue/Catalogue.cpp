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
            if (strcmp(listeTrajet->GetValeur(i)->GetDepart(), depart) == 0 && strcmp(listeTrajet->GetValeur(i)->GetArrivee(), arrivee) == 0)
            {
                cptTrajet++;
                listeTrajet->GetValeur(i)->Afficher();

            }


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
    delete listeTrajetEnSimple; //delete la liste pour ne pas avoir de doubons
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
        cout << "FIN" << endl;
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
                cout << "Ajout : " << trajet->GetTransport() << endl;
                itineraireActuel.Ajouter(trajet);

                // Recherche récursive pour l'itinéraire suivant
                
                RechercheAvanceeGabin(depart, arrivee, itineraires, itineraireActuel);

                // Retirer le trajet de l'itinéraire actuel pour explorer d'autres possibilités
                itineraireActuel.GetMaillon(itineraireActuel.GetTaille() - 1)->ModifierValeur(nullptr) ; //rend null le pointeur pour ne pas delete le trajet
                itineraireActuel.Erase(itineraireActuel.GetTaille() - 1);
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


void Catalogue::TestErase()
{
    Simplification();
    listeTrajetEnSimple->Afficher();
    cout << "Taille : " << listeTrajetEnSimple->GetTaille() << endl;
    cout << "Suppr" << endl;
    listeTrajetEnSimple->Erase(0);
    cout << "Taille : " << listeTrajetEnSimple->GetTaille() << endl;
    listeTrajetEnSimple->Erase(0);
    cout << "Taille : " << listeTrajetEnSimple->GetTaille() << endl;
    listeTrajetEnSimple->Afficher();

}

