#include <iostream>
#include <cstring>
#include "Catalogue/Catalogue.h"
#include "Trajet/Trajet.h"
#include "Trajet/TrajetSimple.h"
#include "Trajet/TrajetCompose.h"
#define MAX 50
using namespace std;

int main()
{

    // Création d'un catalogue de trajets
    Catalogue catalogueTrajet;

    while (true)
    {
        cout << "Que voulez-vous faire ?" << endl;
        cout << "1. Afficher le catalogue" << endl;
        cout << "2. Ajouter un trajet au catalogue" << endl;
        cout << "3. Rechercher simple d'un trajet" << endl;
        cout << "4. Recherche avancée d'un trajet" << endl;
        cout << "5. Quitter" << endl
             << endl;

        int choix;
        cin >> choix; // Choix de l'utilisateur

        switch (choix)
        {
        // Affichage du catalogue
        case 1:
            catalogueTrajet.Afficher(); // Affichage du catalogue
            cout << endl;
            break;

        // Ajout d'un trajet
        case 2:
        {
            cout << "Voulez vous rentrer un trajet simple ou un trajet composée ?" << endl;
            cout << "1. Trajet simple" << endl;
            cout << "2. Trajet composé" << endl;

            int choixTrajet;
            cin >> choixTrajet; // Choix de l'utilisateur

            // Ajout d'un trajet simple
            if (choixTrajet == 1)
            {
                // Ajout d'un trajet simple

                char *depart = new char[MAX];
                char *arrivee = new char[MAX];
                char *moyenTransport = new char[MAX];

                cout << "Veuillez rentrer le départ du trajet : " << endl;
                cin >> depart;
                cout << "Veuillez rentrer l'arrivée du trajet : " << endl;
                cin >> arrivee;
                cout << "Veuillez rentrer le moyen de transport du trajet : " << endl;
                cin >> moyenTransport;

                TrajetSimple *trajetSimple = new TrajetSimple(depart, arrivee, moyenTransport); // Création du trajet simple

                catalogueTrajet.Ajouter(trajetSimple); // Ajout du trajet simple au catalogue
                // catalogueTrajet.AjouterMulti(trajetSimple); //Ajoute à la liste multi du catalogue le trajet simple (Gabin)
                delete[] depart;
                delete[] arrivee;
                delete[] moyenTransport;
                cout << "Fin de la création du trajet simple" << endl
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
                cout << "Veuillez rentrer le départ du trajet global: " << endl
                     << endl;
                cin >> departTrajetCompose;
                cout << "Veuillez rentrer l'arrivée du trajet global : " << endl
                     << endl;
                cin >> arriveeTrajetCompose;

                char *arriveTrajetSimple = new char[MAX];
                do
                {
                    char *departTrajetSimple = new char[MAX];
                    char *moyenTransportTrajetSimple = new char[MAX];

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

                    cout << "Départ du trajet simple n°" << Etape << " : " << departTrajetSimple << endl; // Affichage du départ du trajet simple "n°Etape
                    cout << "Veuillez rentrer l'arrivée du trajet simple n°" << Etape << " :" << endl;
                    cin >> arriveTrajetSimple;

                    cout << "Veuillez rentrer le moyen de transport du trajet simple n°" << Etape << " :" << endl;
                    cin >> moyenTransportTrajetSimple;

                    TrajetSimple *trajetSimple = new TrajetSimple(departTrajetSimple, arriveTrajetSimple, moyenTransportTrajetSimple);
                    listeTrajetSimple.Ajouter(trajetSimple);

                    // catalogueTrajet.AjouterMulti(trajetSimple); //ajoute dans la liste multi du catalogue (Gabin)
                    delete[] moyenTransportTrajetSimple;
                    delete[] departTrajetSimple;
                    Etape++;

                } while (strcmp(arriveTrajetSimple, arriveeTrajetCompose) != 0); // Tant que l'arrivée du trajet simple est différente de l'arrivée du trajet global

                delete[] arriveTrajetSimple;

                // Ajout du trajet composé au catalogue
                TrajetCompose *trajetCompose = new TrajetCompose(listeTrajetSimple);
                catalogueTrajet.Ajouter(trajetCompose);
                delete trajetCompose;

                cout << "Fin de la création du trajet composé" << endl
                     << endl;
            }
            else
            {
                // Choix de l'utilisateur invalide
                cout << "Erreur, veuillez rentrer un choix valide" << endl;
            }
            break;
        }

        // Recherche d'un trajet simple
        case 3:
        {
            // Recherche d'un trajet
            cout << "Veuillez rentrer le départ du trajet simple souhaité : " << endl;
            char *depart = new char[MAX];
            cin >> depart;
            cout << "Veuillez rentrer l'arrivée du trajet simple souhaité : " << endl;
            char *arrivee = new char[MAX];
            cin >> arrivee;

            catalogueTrajet.Rechercher(depart, arrivee); // Recherche du trajet simple

            delete[] depart;
            delete[] arrivee;
            break;
        }

        // Recherche d'un trajet composé
        case 4:
        {

            cout << "Veuillez rentrer le départ du trajet souhaité : " << endl;
            char *depart = new char[MAX];
            cin >> depart;
            cout << "Veuillez rentrer l'arrivée du trajet souhaité : " << endl;
            char *arrivee = new char[MAX];
            cin >> arrivee;

            catalogueTrajet.RechercheAvancee(depart, arrivee); // Recherche du trajet
            delete[] depart;
            delete[] arrivee;
            break;
        }

        // Quitter le programme
        case 5:
            cout << "Fin du programme" << endl;
            return 0;
            break;

        default:
            cout << "Erreur, veuillez rentrer un choix valide" << endl;
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
