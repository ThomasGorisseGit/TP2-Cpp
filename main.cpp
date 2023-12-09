#include <iostream>
#include <cstring>
#include "Catalogue/Catalogue.h"
#include "Trajet/Trajet.h"
#include "Trajet/TrajetSimple.h"
#include "Trajet/TrajetCompose.h"


#define MAX 50

// Couleurs pour l'affichage
#define DEBUT_BOLD_RED "\033[1;31m"
#define FIN "\033[0m"
#define DEBUT_BOLD_GREEN "\033[1;32m"
#define BOLD_WHITE "\033[1;37m"
#define DEBUT_BACKGROUND_GREEN "\033[42m"

using namespace std;

int main()
{

    // Création d'un catalogue de trajets
    Catalogue catalogueTrajet;

    while (true)
    {
        cout << BOLD_WHITE << "Que voulez-vous faire ?" << FIN << endl;
        cout << BOLD_WHITE << "1. " << FIN << "Afficher le catalogue " << endl;
        cout << BOLD_WHITE << "2. " << FIN << "Ajouter un trajet" << endl;
        cout << BOLD_WHITE << "3. " << FIN << "Recherche d'un trajet" << endl;
        cout << BOLD_WHITE << "4. " << FIN << "Recherche avancée" << endl;
        cout << BOLD_WHITE << "5. " << FIN << DEBUT_BOLD_RED << "Quitter le programme" << FIN << endl;
        cout << BOLD_WHITE << "6. " << FIN << DEBUT_BOLD_RED << "Recherche avancée Gabin" << FIN << endl
             << endl;

        int choix;

        // Erreur si l'utilisateur ne rentre pas un nombre
        if (!(cin >> choix))
        {
            cout << DEBUT_BOLD_RED << "Erreur lors de la saisie, veuillez rentrer un nombre" << FIN
                 << endl
                 << endl;

            // Effacer le tampon d'entrée jusqu'à la nouvelle ligne
            cin.clear();
            cin.ignore(2147483647, '\n');

            // Ignorer la suite du code et demander à nouveau la saisie
            continue;
        }

        switch (choix)
        {
        // Affichage du catalogue
        case 1:
        {
            // Création de deux listes de trajets simples et composés
            Liste<Trajet> *listeTrajetSimple = new Liste<Trajet>;
            Liste<Trajet> *listeTrajetCompose = new Liste<Trajet>;

            // Remplissage des deux listes
            catalogueTrajet.GetTrajetSimpleEtCompose(listeTrajetSimple, listeTrajetCompose);

            // Affichage des trajets simples et composés
            catalogueTrajet.Afficher(listeTrajetSimple, listeTrajetCompose);

            cout << endl;
            break;
        }

        // Ajout d'un trajet
        case 2:
        {
            cout << BOLD_WHITE << "Voulez vous rentrer un trajet simple ou un trajet composée ?" << FIN << endl;
            cout << BOLD_WHITE << "1. " << FIN << " Trajet simple" << endl;
            cout << BOLD_WHITE << "2. " << FIN << " Trajet composé" << endl;

            int choixTrajet;
            cin >> choixTrajet; // Choix de l'utilisateur

            // Ajout d'un trajet simple
            if (choixTrajet == 1)
            {
                // Ajout d'un trajet simple

                char *depart = new char[MAX];
                char *arrivee = new char[MAX];
                char *moyenTransport = new char[MAX];

                cout << BOLD_WHITE << "Veuillez rentrer le départ du trajet : " << FIN << endl;
                cin >> depart;
                cout << BOLD_WHITE << "Veuillez rentrer l'arrivée du trajet : " << FIN << endl;
                cin >> arrivee;
                cout << BOLD_WHITE << "Veuillez rentrer le moyen de transport du trajet : " << FIN << endl;
                cin >> moyenTransport;

                TrajetSimple *trajetSimple = new TrajetSimple(depart, arrivee, moyenTransport); // Création du trajet simple

                catalogueTrajet.Ajouter(trajetSimple); // Ajout du trajet simple au catalogue
                // catalogueTrajet.AjouterMulti(trajetSimple); //Ajoute à la liste multi du catalogue le trajet simple (Gabin)
                delete[] depart;
                delete[] arrivee;
                delete[] moyenTransport;
                cout << DEBUT_BOLD_GREEN << "Fin de la création du trajet simple" << FIN << endl
                     << endl;
            }
            else if (choixTrajet == 2)
            {

                // Ajout d'un trajet composé
                bool isFirstEtape = true;
                int Etape = 1;
                char *departTrajetCompose = new char[MAX];
                char *arriveeTrajetCompose = new char[MAX];

                Liste<TrajetSimple> listeTrajetSimple;
                cout << BOLD_WHITE << "Veuillez rentrer le départ du trajet global : " << FIN << endl
                     << endl;
                cin >> departTrajetCompose;
                cout << BOLD_WHITE << "Veuillez rentrer l'arrivée du trajet global : " << FIN << endl
                     << endl;
                cin >> arriveeTrajetCompose;

                char *arriveTrajetSimple = new char[MAX];
                char *departTrajetSimple = new char[MAX];
                char *moyenTransportTrajetSimple = new char[MAX];
                do
                {

                    // Si on ajoute le premier trajet simple, on récupère le départ du trajet global
                    if (isFirstEtape)
                    {
                        strcpy(departTrajetSimple, departTrajetCompose);
                        isFirstEtape = false;
                    }
                    else
                    {
                        strcpy(departTrajetSimple, arriveTrajetSimple);
                    }

                    cout << "Départ du trajet simple n°" << Etape << " : " DEBUT_BACKGROUND_GREEN << departTrajetSimple << FIN << endl; // Affichage du départ du trajet simple "n°Etape
                    cout << BOLD_WHITE << "Veuillez rentrer l'arrivée du trajet simple n°" << Etape << " :" << FIN << endl;
                    cin >> arriveTrajetSimple;

                    cout << BOLD_WHITE << "Veuillez rentrer le moyen de transport du trajet simple n°" << Etape << " :" << FIN << endl;
                    cin >> moyenTransportTrajetSimple;

                    TrajetSimple *trajetSimple = new TrajetSimple(departTrajetSimple, arriveTrajetSimple, moyenTransportTrajetSimple);
                    listeTrajetSimple.Ajouter(trajetSimple);

                    // catalogueTrajet.AjouterMulti(trajetSimple); //ajoute dans la liste multi du catalogue (Gabin)

                    Etape++;

                } while (strcmp(arriveTrajetSimple, arriveeTrajetCompose) != 0); // Tant que l'arrivée du trajet simple est différente de l'arrivée du trajet global
                delete[] moyenTransportTrajetSimple;
                delete[] departTrajetSimple;
                delete[] arriveTrajetSimple;
                delete[] departTrajetCompose;
                delete[] arriveeTrajetCompose;

                // Ajout du trajet composé au catalogue
                TrajetCompose *trajetCompose = new TrajetCompose(listeTrajetSimple);
                catalogueTrajet.Ajouter(trajetCompose);

                cout << DEBUT_BOLD_GREEN << "Fin de la création du trajet composé" << FIN << endl
                     << endl;
            }
            else
            {
                // Choix de l'utilisateur invalide
                cout << DEBUT_BOLD_RED << "Erreur lors de la saisie, veuillez rentrer un choix valide (1 ou 2)" << FIN
                     << endl
                     << endl;
            }
            break;
        }

        // Recherche d'un trajet simple
        case 3:
        {
            // Recherche d'un trajet
            cout << BOLD_WHITE << "Veuillez rentrer le départ du trajet simple souhaité : " << FIN << endl;
            char *depart = new char[MAX];
            cin >> depart;
            cout << BOLD_WHITE << "Veuillez rentrer l'arrivée du trajet simple souhaité : " << FIN << endl;
            char *arrivee = new char[MAX];
            cin >> arrivee;

            catalogueTrajet.Rechercher(depart, arrivee,1); // Recherche du trajet simple

            delete[] depart;
            delete[] arrivee;
            break;
        }

        // Recherche d'un trajet composé
        case 4:
        {

            cout << BOLD_WHITE << "Veuillez rentrer le départ du trajet souhaité : " << FIN << endl;
            char *depart = new char[MAX];
            cin >> depart;
            cout << BOLD_WHITE << "Veuillez rentrer l'arrivée du trajet souhaité : " << FIN << endl;
            char *arrivee = new char[MAX];
            cin >> arrivee;

            catalogueTrajet.RechercheAvancee(depart, arrivee); // Recherche du trajet
            delete[] depart;
            delete[] arrivee;
            break;
        }

        case 6:
        {

            cout << BOLD_WHITE << "Veuillez rentrer le départ du trajet souhaité : " << FIN << endl;
            char *depart = new char[MAX];
            cin >> depart;
            cout << BOLD_WHITE << "Veuillez rentrer l'arrivée du trajet souhaité : " << FIN << endl;
            char *arrivee = new char[MAX];
            cin >> arrivee;

            Liste<TrajetSimple> *itineraires = new Liste<TrajetSimple>;  // Liste pour stocker les itinéraires trouvés
            Liste<TrajetSimple> *itineraireActuel = new Liste<TrajetSimple>;  // Liste pour stocker l'itinéraire actuel pendant la recherche
            catalogueTrajet.RechercheAvanceeGabin(depart, arrivee, *itineraires, *itineraireActuel); // Recherche du trajet
            itineraires->Afficher();
            delete[] depart;
            delete[] arrivee;
            delete itineraires;
            delete itineraireActuel;
            break;
        }

        // Quitter le programme
        case 5:
            cout << DEBUT_BOLD_RED << "Fin du programme" << FIN << endl;
            return 0;
            break;

        default:
            cout << DEBUT_BOLD_RED << "Erreur lors de la saisie, veuillez rentrer un choix valide (1, 2, 3, 4 ou 5)" << FIN
                 << endl;

            break;
        }
    }

    // Catalogue catalogueTrajet;
    // catalogueTrajet.Ajouter(new TrajetSimple("Paris", "Lyon", "Train"));
    // Liste<Trajet> * liste= new Liste<Trajet>;
    // catalogueTrajet.Rechercher("Paris", "Lyon", *liste);
    // liste->Afficher();

    // catalogueTrajet.Ajouter(new TrajetSimple("Lyon", "Marseille", "Train"));
    // catalogueTrajet.Ajouter(new TrajetSimple("Lyon", "Cannes", "Train"));
    //  catalogueTrajet.Ajouter(new TrajetSimple("Troucoin", "Marseille", "Train"));
    //  catalogueTrajet.Ajouter(new TrajetSimple("Troucoin", "Cannes", "Train"));
    //  catalogueTrajet.Ajouter(new TrajetSimple("Marseille", "Nice", "Train"));
    //  catalogueTrajet.Ajouter(new TrajetSimple("Nice", "Lyon", "Train"));
    // catalogueTrajet.RechercheAvancee("Paris", "Cannes");
    cout << "      " << endl;
    return 0;
}
