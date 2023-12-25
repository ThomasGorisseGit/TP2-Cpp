#include <iostream>
#include <cstring>
#include "Catalogue.h"
#include "../Trajet/Trajet.h"
#include "../Liste/Liste.h"

// Couleur pour l'affichage
#define BOLD_WHITE "\033[1m"
#define FIN "\033[0m"
#define DEBUT_BOLD_GREEN "\033[1;32m"
#define DEBUT_BOLD_RED "\033[1;31m"
#define DOUBLE_ENDL std::endl \
                        << std::endl
#define TAB "\t"

using namespace std;

Catalogue::Catalogue()
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
    this->listeTrajet = new Liste<Trajet>;
}

Catalogue::Catalogue(const Catalogue &unCatalogue)
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Catalogue>" << endl;
#endif
    this->listeTrajet = new Liste<Trajet>; // Création d'une nouvelle liste de trajets

    for (unsigned int i = 0; i < unCatalogue.listeTrajet->GetTaille(); i++)
    {
        this->listeTrajet->Ajouter(unCatalogue.listeTrajet->GetValeur(i));
    }
}

Catalogue::~Catalogue()
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
    delete listeTrajet;
}

void Catalogue::Ajouter(Trajet *trajet)
{
    this->listeTrajet->Ajouter(trajet); // Appel de la méthode ajouter de la classe Liste
}

void Catalogue::Afficher(Liste<Trajet> *listeTrajetSimple, Liste<Trajet> *listeTrajetCompose) const
{

    cout << BOLD_WHITE << "-----------------------------------------------------------------" << FIN << endl;
    cout << BOLD_WHITE << "---------------------------" << DEBUT_BOLD_GREEN << "BIENVENUE" << FIN << BOLD_WHITE << "-----------------------------" << FIN << endl;
    cout << BOLD_WHITE << "---------------------------" << DEBUT_BOLD_GREEN << "SUR" << FIN << "    " << DEBUT_BOLD_GREEN << BOLD_WHITE << "LE" << FIN << BOLD_WHITE << "-----------------------------" << FIN << endl;
    cout << BOLD_WHITE << "---------------------------" << DEBUT_BOLD_GREEN << "CATALOGUE" << FIN << BOLD_WHITE << "-----------------------------" << FIN << endl;
    cout << BOLD_WHITE << "-----------------------------------------------------------------" << FIN << endl
         << endl;

    if (this->listeTrajet->GetTaille() == 0)
    {
        cout << BOLD_WHITE << "Le catalogue est vide" << FIN << endl;
        return;
    }

    // Si il existe des trajets simples dans le catalogue
    if (listeTrajetSimple->GetTaille() != 0)
    {
        cout << BOLD_WHITE << "Voici la liste des trajets simples :" << FIN << DOUBLE_ENDL;
        listeTrajetSimple->Afficher();
        cout << endl;
    }
    else
    {
        cout << BOLD_WHITE << "Il n'y a pas de trajets simples dans le catalogue" << FIN << DOUBLE_ENDL;
    }

    // Si il existe des trajets composés dans le catalogue
    if (listeTrajetCompose->GetTaille() != 0)
    {
        cout << BOLD_WHITE << "Voici la liste des trajets composés :" << FIN << DOUBLE_ENDL;
        listeTrajetCompose->Afficher();
        cout << endl;
    }
    else
    {
        cout << BOLD_WHITE << "Il n'y a pas de trajets composés dans le catalogue" << FIN << DOUBLE_ENDL;
    }
}

Liste<TrajetSimple> *Catalogue::Rechercher(const char *depart, const char *arrivee) const
// Algorithme :
//      Parcours de la liste des trajets et comparaison des chaînes de caractère pour déterminer lesquels sont égales.
//      Si le trajet est simple, on le compare directement.
//      Si le trajet est composé, on parcours les trajets simples qui le composent et on les compare.
//      On retourne une liste de trajets simples qui correspondent à la recherche.
{
    Liste<TrajetSimple> *listeChemins = new Liste<TrajetSimple>;
    unsigned int cptTrajet = 0;
    unsigned int taille = listeTrajet->GetTaille();
    cout << endl;
    for (unsigned int i = 0; i < taille; i++)
    {
        if (listeTrajet->GetValeur(i)->GetType() == 1) // est un trajet simple
        {
            // Si le depart du trajet simple est la même que celui en parametre
            // et que l'arrivée est la même que celle en parametre
            if (strcmp(listeTrajet->GetValeur(i)->GetDepart(), depart) == 0 && strcmp(listeTrajet->GetValeur(i)->GetArrivee(), arrivee) == 0)
            {
                // On affiche le trajet simple
                cout << BOLD_WHITE << "Trajet Simples : " << FIN;
                listeTrajet->GetValeur(i)->Afficher();
                cout << endl;
                cptTrajet++;
                TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i), listeTrajet->GetValeur(i)->GetTransport());
                listeChemins->Ajouter(TrajetSimpleRemplissage);
            }
        }
        else // C'est un trajet composé
        {

            // On recherche dans les trajets simples qui composent le trajet composé
            if (strcmp(listeTrajet->GetValeur(i)->GetDepart(), depart) == 0 && strcmp(listeTrajet->GetValeur(i)->GetArrivee(), arrivee) == 0)
            {
                cptTrajet++;
                cout << BOLD_WHITE << "Trajet Composé : " << FIN;
                listeTrajet->GetValeur(i)->Afficher();
                cout << endl;
            }

            unsigned int tailleTrajetCompose = listeTrajet->GetValeur(i)->GetTailleTrajet();

            // On parcours tous les trajets simples qui composent le trajet composé
            for (unsigned int j = 0; j < tailleTrajetCompose; j++)
            {
                // Si le depart du trajet simple est la même que celui en parametre et que l'arrivée est la même que celle en parametre
                if (strcmp(listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetDepart(), depart) == 0 &&
                    strcmp(listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetArrivee(), arrivee) == 0)
                {

                    // On affiche le trajet simple
                    cout << BOLD_WHITE << "Partie d'un trajet Composé : " << FIN;
                    listeTrajet->GetValeur(i)->GetTrajetSimple(j)->Afficher();
                    cout << endl;

                    // On ajoute le trajet simple à la liste des trajets simples (pas utilisé)
                    TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i)->GetTrajetSimple(j),
                                                                             listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetTransport());
                    listeChemins->Ajouter(TrajetSimpleRemplissage);
                    cptTrajet++;
                }
            }
        }
    }

    // Si aucun trajet n'a été trouvé
    if (!cptTrajet)
    {
        cout << "Pas de trajet correspondant trouvé parmis les " << taille << " trajets." << endl
             << endl;
    }
    return listeChemins;
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

void Catalogue::Simplification(Liste<TrajetSimple> *listeTrajetSimple)
{
    unsigned int taille = listeTrajet->GetTaille();

    for (unsigned int i = 0; i < taille; i++)
    {

        if (listeTrajet->GetValeur(i)->GetType() == 1) // Trajet simple
        {
            TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i), listeTrajet->GetValeur(i)->GetTransport());
            listeTrajetSimple->Ajouter(TrajetSimpleRemplissage);
        }

        else // Trajet composé
        {
            // On ajoute tous les trajets simples compris dans ce trajet composé
            unsigned int tailleTrajetCompose = listeTrajet->GetValeur(i)->GetTailleTrajet();
            for (unsigned int j = 0; j < tailleTrajetCompose; j++)
            {
                TrajetSimple *TrajetSimpleRemplissage = new TrajetSimple(*listeTrajet->GetValeur(i)->GetTrajetSimple(j),
                                                                         listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetTransport());
                listeTrajetSimple->Ajouter(TrajetSimpleRemplissage);
            }
        }
    }
}

void Catalogue::RechercheAvancee(const char *depart, const char *arrivee, Liste<TrajetSimple> &itineraires, Liste<TrajetSimple> &itineraireActuel, Liste<TrajetSimple> *listeTrajetEnSimple)
// Algorithme :
//      On parcours tous les trajets simples du catalogue et on compare le départ du trajet simple avec le dernier point de l'itinéraire actuel.
//      Si le départ du trajet simple correspond au dernier point de l'itinéraire actuel, on ajoute le trajet simple à l'itinéraire actuel.
//      On appelle la méthode récursivement avec le dernier point de l'itinéraire actuel comme nouveau point de départ.
//      Si le dernier point de l'itinéraire actuel correspond à l'arrivée, on ajoute l'itinéraire actuel à la liste des itinéraires.
//      On retire le dernier trajet de l'itinéraire actuel (grâce à Erase()) pour explorer d'autres possibilités.
{

    // cout << "Recherche d'un trajet partant de : " << DEBUT_BOLD_GREEN << depart << FIN << " à " << DEBUT_BOLD_GREEN << arrivee << FIN << endl;

    // Si la liste d'itinéraires actuelle atteint la destination, l'ajouter à la liste complète d'itinéraires
    if (itineraireActuel.GetTaille() > 0 &&
        strcmp(itineraireActuel.GetValeur(itineraireActuel.GetTaille() - 1)->GetArrivee(), arrivee) == 0)
    {
        itineraires.Ajouter(&itineraireActuel);
        return;
    }

    // Si la taille de l'itinéraire actuel est positive, on récupère le dernier trajet de l'itinéraire actuel
    // Sinon, c'est le premier trajet de la recherche => dernierTrajet est nullptr
    Trajet *dernierTrajet = itineraireActuel.GetTaille() > 0 ? itineraireActuel.GetValeur(itineraireActuel.GetTaille() - 1) : nullptr;

    for (unsigned int i = 0; i < listeTrajetEnSimple->GetTaille(); ++i)
    {

        TrajetSimple *trajet = listeTrajetEnSimple->GetValeur(i);

        // Vérifier si le départ du trajet correspond au dernier point de l'itinéraire actuel (si il existe, sinon on compare avec le départ de la recherche)
        if (strcmp(trajet->GetDepart(), (dernierTrajet ? dernierTrajet->GetArrivee() : depart)) == 0)
        {

            // Verification si le trajet n'est pas déjà dans l'itinéraire actuel pour éviter les boucles infinies
            if (itineraireActuel.Rechercher(trajet) == 0)
            {
                // Ajouter le trajet à l'itinéraire actuel
                itineraireActuel.Ajouter(trajet);

                // Appel récursif avec le dernier point de l'itinéraire actuel comme nouveau point de départ
                RechercheAvancee(depart, arrivee, itineraires, itineraireActuel, listeTrajetEnSimple);

                // Retirer le trajet de l'itinéraire actuel pour explorer d'autres possibilités
                itineraireActuel.GetMaillon(itineraireActuel.GetTaille() - 1)->ModifierValeur(nullptr); // rend nullptr le pointeur pour ne pas delete le trajet
                itineraireActuel.Erase(itineraireActuel.GetTaille() - 1);                               // retire le trajet de l'itinéraire actuel
            }
        }
    }
}

void Catalogue::SauvegardeCatalogueSansCritere(const char *nomFichier) const
{

    ofstream fichier(nomFichier, ios::out | ios::trunc); // ouverture en écriture avec effacement du fichier ouvert

    if (fichier)
    {
        unsigned int taille = listeTrajet->GetTaille();
        for (unsigned int i = 0; i < taille; i++)
        {
            if (listeTrajet->GetValeur(i)->GetType() == 1) // est un trajet simple
            {
                this->sauvegardeSimple(fichier, i);
            }
            else // est un trajet compose
            {
                this->sauvegardeCompose(fichier, i);
            }
        }
        fichier.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}

void Catalogue::SauvegardeCatalogueSelonType(const char *nomFichier, int type) const
{

    ofstream fichier(nomFichier, ios::out | ios::trunc); // ouverture en écriture avec effacement du fichier ouvert

    if (fichier)
    {
        unsigned int taille = listeTrajet->GetTaille();
        for (unsigned int i = 0; i < taille; i++)
        {
            if (type == 1 && listeTrajet->GetValeur(i)->GetType() == type) // est un trajet simple
            {
                this->sauvegardeSimple(fichier, i);
            }
            else if (type == 2 && listeTrajet->GetValeur(i)->GetType() == type) // est un trajet compose
            {
                this->sauvegardeCompose(fichier, i);
            }
        }
        fichier.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}

void Catalogue::SauvegardeCatalogueDepartArrivee(const char *nomFichier, const char *ville, int type) const
{
    // type = 1 : depart
    // type = 2 : arrivee
    ofstream fichier(nomFichier, ios::out | ios::trunc); // ouverture en écriture avec effacement du fichier ouvert

    if (fichier)
    {
        unsigned int taille = listeTrajet->GetTaille();
        for (unsigned int i = 0; i < taille; i++)
        {
            if ((strcmp(listeTrajet->GetValeur(i)->GetDepart(), ville) == 0 && type == 1) || (strcmp(listeTrajet->GetValeur(i)->GetArrivee(), ville) == 0 && type == 2)) // est un trajet simple
            {
                if (listeTrajet->GetValeur(i)->GetType() == 1) // est un trajet simple
                {
                    this->sauvegardeSimple(fichier, i);
                }
                else // est un trajet compose
                {
                    this->sauvegardeCompose(fichier, i);
                }
            }
        }
        fichier.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}

void Catalogue::sauvegardeSimple(ofstream &fichier, int i) const
{
    fichier << "1 " << endl
            << TAB << listeTrajet->GetValeur(i)->GetDepart() << " " << listeTrajet->GetValeur(i)->GetArrivee() << " " << listeTrajet->GetValeur(i)->GetTransport() << endl;
}
void Catalogue::sauvegardeCompose(ofstream &fichier, int i) const
{

    fichier << "2 " << listeTrajet->GetValeur(i)->GetTailleTrajet() << endl;
    unsigned int tailleTrajetCompose = listeTrajet->GetValeur(i)->GetTailleTrajet();
    for (unsigned int j = 0; j < tailleTrajetCompose; j++)
    {
        fichier << TAB << listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetDepart() << " " << listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetArrivee() << " " << listeTrajet->GetValeur(i)->GetTrajetSimple(j)->GetTransport() << endl;
    }
}

void Catalogue::SauvegardeCatalogueIntervalle(const char *nomFichier, int debut, unsigned int fin) const
{

    ofstream fichier(nomFichier, ios::out | ios::trunc); // ouverture en écriture avec effacement du fichier ouvert

    if (debut < 0)
    {
        cout << DEBUT_BOLD_RED << "L'indice de début doit être positif" << FIN << endl;
        return;
    }
    else if (fin >= listeTrajet->GetTaille())
    {
        cout << DEBUT_BOLD_RED << "L'indice de fin doit être inférieur à la taille du catalogue" << FIN << endl;
        return;
    }

    if (fichier)
    {
        for (unsigned int i = debut; i <= fin; i++)
        {
            if (listeTrajet->GetValeur(i)->GetType() == 1) // est un trajet simple
            {
                this->sauvegardeSimple(fichier, i);
            }
            else // est un trajet compose
            {
                this->sauvegardeCompose(fichier, i);
            }
        }
        fichier.close();
    }
    else
    {
        cout << DEBUT_BOLD_RED << "Impossible d'ouvrir le fichier !" << FIN << endl;
    }
}

void Catalogue::ImporterFichierSansCritere(const char *nomFichier)
{
    ifstream fichier(nomFichier, ios::in); // ouverture en lecture

    if (fichier)
    {
        string ligne;

        while (getline(fichier, ligne))
        {
            // Lecture du premier caractère de la ligne
            string type = ligne.substr(0, 1);

            // Cas d'un trajet simple
            if (type == "1")
            {

                // format :
                // \t DEPART ARRIVEE TRANSPORT

                getline(fichier, ligne); // On parse la ligne suivante

                getline(fichier, ligne); // On parse la ligne suivante

                // On supprime le premier caractère de la ligne (la tabulation)
                ligne.erase(0, 1);
                int pos = ligne.find(" ");
                string depart = ligne.substr(0, pos);

                ligne.erase(0, pos + 1);
                pos = ligne.find(" ");
                string arrivee = ligne.substr(0, pos);

                ligne.erase(0, pos + 1);
                string transport = ligne;
                char *c_transport = new char[transport.length() + 1];

                TrajetSimple *trajetSimple = new TrajetSimple(depart.c_str(), arrivee.c_str(), strcpy(c_transport, transport.c_str()));

                this->Ajouter(trajetSimple);
                delete[] c_transport;
            }

            // Cas d'un trajet composé
            else if (type == "2")
            {

                int tailleTrajetComposee = stoi(ligne.substr(2, 1)); // On récupère la taille du trajet composé

                // format :
                // \t DEPART_GLOBALE ARRIVEE TRANSPORT_1
                // \t DEPART ARRIVEE_GLOBALE TRANSPORT_2

                Liste<TrajetSimple> listeTrajetSimple;

                for (int i = 0; i < tailleTrajetComposee; i++)
                {
                    getline(fichier, ligne); // On parse la ligne suivante

                    // On supprime le premier caractère de la ligne (la tabulation)
                    ligne.erase(0, 1);
                    int pos = ligne.find(" ");
                    string depart = ligne.substr(0, pos);

                    ligne.erase(0, pos + 1);
                    pos = ligne.find(" ");
                    string arrivee = ligne.substr(0, pos);

                    ligne.erase(0, pos + 1);
                    string transport = ligne; // On recupère la dernière composante de la ligne

                    char *c_transport = new char[transport.length() + 1];

                    TrajetSimple *trajetSimple = new TrajetSimple(depart.c_str(), arrivee.c_str(), strcpy(c_transport, transport.c_str()));
                    listeTrajetSimple.Ajouter(trajetSimple);

                    delete[] c_transport;
                }

                // Ajout du trajet composé au catalogue
                TrajetCompose *trajetCompose = new TrajetCompose(listeTrajetSimple);
                this->Ajouter(trajetCompose);
            }
        }
        fichier.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}

void Catalogue::ImporterFichierSelonType(const char *nomFichier, int typeTrajet)
{
    ifstream fichier(nomFichier, ios::in); // ouverture en lecture

    if (fichier)
    {
        string ligne;

        while (getline(fichier, ligne))
        {
            // Lecture du premier caractère de la ligne
            string type = ligne.substr(0, 1);

            // Cas d'un trajet simple
            if (type == "1" && type == to_string(typeTrajet))
            {

                // format :
                // \t DEPART ARRIVEE TRANSPORT

                getline(fichier, ligne); // On parse la ligne suivante

                // On supprime le premier caractère de la ligne (la tabulation)
                ligne.erase(0, 1);
                int pos = ligne.find(" ");
                string depart = ligne.substr(0, pos);

                ligne.erase(0, pos + 1);
                pos = ligne.find(" ");
                string arrivee = ligne.substr(0, pos);

                ligne.erase(0, pos + 1);
                string transport = ligne;
                char *c_transport = new char[transport.length() + 1];

                TrajetSimple *trajetSimple = new TrajetSimple(depart.c_str(), arrivee.c_str(), strcpy(c_transport, transport.c_str()));

                this->Ajouter(trajetSimple);
                delete[] c_transport;
            }

            // Cas d'un trajet composé
            else if (type == "2" && type == to_string(typeTrajet))
            {

                int tailleTrajetComposee = stoi(ligne.substr(2, 1)); // On récupère la taille du trajet composé

                // format :
                // \t DEPART_GLOBALE ARRIVEE TRANSPORT_1
                // \t DEPART ARRIVEE_GLOBALE TRANSPORT_2

                Liste<TrajetSimple> listeTrajetSimple;

                for (int i = 0; i < tailleTrajetComposee; i++)
                {
                    getline(fichier, ligne); // On parse la ligne suivante

                    // On supprime le premier caractère de la ligne (la tabulation)
                    ligne.erase(0, 1);
                    int pos = ligne.find(" ");
                    string depart = ligne.substr(0, pos);

                    ligne.erase(0, pos + 1);
                    pos = ligne.find(" ");
                    string arrivee = ligne.substr(0, pos);

                    ligne.erase(0, pos + 1);
                    string transport = ligne; // On recupère la dernière composante de la ligne

                    char *c_transport = new char[transport.length() + 1];

                    TrajetSimple *trajetSimple = new TrajetSimple(depart.c_str(), arrivee.c_str(), strcpy(c_transport, transport.c_str()));
                    listeTrajetSimple.Ajouter(trajetSimple);

                    delete[] c_transport;
                }

                // Ajout du trajet composé au catalogue
                TrajetCompose *trajetCompose = new TrajetCompose(listeTrajetSimple);
                this->Ajouter(trajetCompose);
            }
        }
        fichier.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}