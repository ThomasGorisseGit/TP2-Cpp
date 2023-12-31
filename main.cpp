#include <iostream>
#include <cstring>
#include "src/Catalogue/Catalogue.h"
#include "src/Trajet/Trajet.h"
#include "src/Trajet/TrajetSimple.h"
#include "src/Trajet/TrajetCompose.h"

#define MAX 50

// Couleurs pour l'affichage
#define DEBUT_BOLD_RED "\033[1;31m"
#define DEBUT_RED "\033[31m"
#define DEBUT_MAGENTA "\033[35m"
#define FIN "\033[0m"
#define DEBUT_BOLD_GREEN "\033[1;32m"
#define BOLD_WHITE "\033[1;37m"
#define DEBUT_BACKGROUND_GREEN "\033[42m"
#define DEBUT_BOLD_BLUE "\033[1;34m"
#define DOUBLE_ENDL std::endl \
                        << std::endl

using namespace std;

int main()
{

    // Création d'un catalogue de trajets
    Catalogue catalogueTrajet;

    while (true)
    {
        cout << endl
             << BOLD_WHITE << "Que voulez-vous faire ?" << FIN << DOUBLE_ENDL;
        cout << BOLD_WHITE << "1. " << FIN << "Afficher le catalogue " << endl;
        cout << BOLD_WHITE << "2. " << FIN << "Ajouter un trajet" << endl;
        cout << BOLD_WHITE << "3. " << FIN << "Recherche d'un trajet" << endl;
        cout << BOLD_WHITE << "4. " << FIN << "Recherche avancée" << endl;
        cout << BOLD_WHITE << "5. " << FIN << DEBUT_RED << "Quitter le programme" << FIN << DOUBLE_ENDL;

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

            listeTrajetSimple->ModifierToutesLesValeursEnNull(); // on vide les listes
            listeTrajetCompose->ModifierToutesLesValeursEnNull();
            delete listeTrajetSimple; // puis on les delete
            delete listeTrajetCompose;

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

                do
                {
                    cout << BOLD_WHITE << "Veuillez rentrer l'arrivée du trajet : " << FIN << endl;
                    cin >> arrivee;
                    if (strcmp(depart, arrivee) == 0)
                        cout << DEBUT_BOLD_RED << "Erreur de saisie, arrivée du trajet identique au départ" << FIN << endl;
                } while (strcmp(depart, arrivee) == 0);

                cout << BOLD_WHITE << "Veuillez rentrer le moyen de transport du trajet : " << FIN << endl;
                cin >> moyenTransport;

                TrajetSimple *trajetSimple = new TrajetSimple(depart, arrivee, moyenTransport); // Création du trajet simple

                catalogueTrajet.Ajouter(trajetSimple); // Ajout du trajet simple au catalogue

                cout << DEBUT_BOLD_GREEN << "Fin de la création du trajet simple : " << depart << " vers " << arrivee << " ." << FIN << endl
                     << endl;
                delete[] depart;
                delete[] arrivee;
                delete[] moyenTransport;
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

                do
                {
                    cout << BOLD_WHITE << "Veuillez rentrer l'arrivée du trajet global : " << FIN << endl;
                    cin >> arriveeTrajetCompose;
                    if (strcmp(departTrajetCompose, arriveeTrajetCompose) == 0)
                    {
                        cout << DEBUT_BOLD_RED << "Erreur de saisie, arrivée du trajet identique au départ" << FIN << endl;
                    }
                } while (strcmp(departTrajetCompose, arriveeTrajetCompose) == 0);

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

            Liste<TrajetSimple> *ListeRecherche = catalogueTrajet.Rechercher(depart, arrivee);

            delete[] depart;
            delete[] arrivee;
            delete ListeRecherche;
            break;
        }
        // Recherche avancée
        case 4:
        {

            cout << BOLD_WHITE << "Veuillez rentrer le départ du trajet souhaité : " << FIN << endl;
            char *depart = new char[MAX];
            cin >> depart;
            cout << BOLD_WHITE << "Veuillez rentrer l'arrivée du trajet souhaité : " << FIN << endl;
            char *arrivee = new char[MAX];
            cin >> arrivee;

            Liste<TrajetSimple> * listeTrajetSimple = new Liste<TrajetSimple>;

            catalogueTrajet.Simplification(listeTrajetSimple);

            Liste<TrajetSimple> *itineraires = new Liste<TrajetSimple>;                         // Liste pour stocker les itinéraires trouvés
            Liste<TrajetSimple> *itineraireActuel = new Liste<TrajetSimple>;                    // Liste pour stocker l'itinéraire actuel pendant la recherche
            catalogueTrajet.RechercheAvancee(depart, arrivee, *itineraires, *itineraireActuel,listeTrajetSimple); // Recherche du trajet
            cout << endl
                 << BOLD_WHITE << "Affichage de l'itinéraire : " << FIN << DOUBLE_ENDL;

            unsigned int tailleIti = itineraires->GetTaille();
            for (unsigned int i = 0; i < tailleIti; i++)
            {

                itineraires->GetValeur(i)->AfficherPetit();
                if (strcmp(itineraires->GetValeur(i)->GetArrivee(), arrivee) == 0)
                {

                    cout << endl
                         << " -------------------------------" << endl; // Séparation entre les différents itinéraires
                }
                else if (i != tailleIti - 1)
                    cout << DEBUT_MAGENTA << " ➔ " << FIN;
            }

            delete[] depart;
            delete[] arrivee;

            itineraireActuel->ModifierToutesLesValeursEnNull();
            delete itineraireActuel;

            itineraires->ModifierToutesLesValeursEnNull();
            delete itineraires;

            delete listeTrajetSimple;

            break;
        }

        case 42:
        {
            cout << R"(⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣶⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⠿⠟⠛⠻⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣆⣀⣀⠀⣿⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠻⣿⣿⣿⠅⠛⠋⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢼⣿⣿⣿⣃⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣟⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣛⣛⣫⡄⠀⢸⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⡆⠸⣿⣿⣿⡷⠂⠨⣿⣿⣿⣿⣶⣦⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣾⣿⣿⣿⣿⡇⢀⣿⡿⠋⠁⢀⡶⠪⣉⢸⣿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⡏⢸⣿⣷⣿⣿⣷⣦⡙⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣇⢸⣿⣿⣿⣿⣿⣷⣦⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣵⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                     Get RickRolled                )"
                 << endl;
        }

        // Quitter le programme
        case 5:
            cout << DEBUT_BOLD_RED << "Fin du programme" << FIN << endl;
            cout << "Crédit : T.Gorisse - P.Brossat - G.Joussot-Dubien - C.Roubaud" << endl;
            return 0;
            break;

        default:
            cout << DEBUT_BOLD_RED << "Erreur lors de la saisie, veuillez rentrer un choix valide (1, 2, 3, 4 ou 5)" << FIN
                 << endl;

            break;
        }
    }
    cout << endl;
    return 0;
}
