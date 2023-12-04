#include <iostream>
#include <cstring>
#include "Catalogue/Catalogue.h"
#include "Trajet/Trajet.h"
#include "Trajet/TrajetSimple.h"
#include "Trajet/TrajetCompose.h"
#define MAX 50
using namespace std;

// Affichage du catalogue
// Ajouter un trajet au catalogue => Simple ou Composé
// Si ajouter un trajet composé, il faut ajouter les trajets simples qui le composent
// Sinon si on ajoute un trajet simple, on rentre juste l'arrivée et le départ
// (Recherche d'un trajet dans le catalogue)
// (Suppression d'un trajet dans le catalogue) // optionnel

int main()
{
    // Création d'un catalogue de trajets

    Catalogue catalogueTrajet;

    while (true)
    {
        cout << "Que voulez-vous faire ?" << endl;
        cout << "1. Afficher le catalogue" << endl;
        cout << "2. Ajouter un trajet au catalogue" << endl;
        cout << "3. Rechercher un trajet" << endl;
        cout << "4. Quitter" << endl;

        int choix;
        cin >> choix; // Choix de l'utilisateur

        switch (choix)
        {
        case 1:
            catalogueTrajet.Afficher(); // Affichage du catalogue
            cout << endl;               // Pour la lisibilité
            break;
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
                delete[] depart;
                delete[] arrivee;
                delete[] moyenTransport;
                cout << "Fin de la création du trajet simple" << endl;
            }
            else if (choixTrajet == 2)
            {

                // Ajout d'un trajet composé
                bool isFirstEtape = true;
                int Etape = 1;
                char *departTrajetCompose = new char[MAX];
                char *arriveeTrajetCompose = new char[MAX];

                Liste<TrajetSimple> listeTrajetSimple;
                cout << "Veuillez rentrer le départ du trajet global: " << endl;
                cin >> departTrajetCompose;
                cout << "Veuillez rentrer l'arrivée du trajet global : " << endl;
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

                    cout << "Veuillez rentrer l'arrivée du trajet simple n°" << Etape << " :" << endl;
                    cin >> arriveTrajetSimple;

                    cout << "Veuillez rentrer le moyen de transport du trajet simple n°" << Etape << " :" << endl;
                    cin >> moyenTransportTrajetSimple;

                    TrajetSimple *trajetSimple = new TrajetSimple(departTrajetSimple, arriveTrajetSimple, moyenTransportTrajetSimple);
                    listeTrajetSimple.Ajouter(trajetSimple);
                    delete[] moyenTransportTrajetSimple;
                    delete[] departTrajetSimple;
                    Etape++; // Incrémentation du numéro de l'étape
                } while (strcmp(arriveTrajetSimple, arriveeTrajetCompose) != 0);

                delete[] arriveTrajetSimple;

                cout << "Fin de la création du trajet composé" << endl;
            }
            else
            {
                // Choix de l'utilisateur invalide
                cout << "Erreur, veuillez rentrer un choix valide" << endl;
            }
            break;
        }

        case 3:
        {
            // Recherche d'un trajet
            cout << "Veuillez rentrer le départ du trajet souhaité : " << endl;
            char *depart = new char[MAX];
            cin >> depart;
            cout << "Veuillez rentrer l'arrivée du trajet souhaité : " << endl;
            char *arrivee = new char[MAX];
            cin >> arrivee;

            catalogueTrajet.initSearch(depart, arrivee); // Recherche du trajet
            delete[] depart;
            delete[] arrivee;
            break;
        }
        case 4:
            // Quitter le programme
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
    // catalogueTrajet.Ajouter(new TrajetSimple("Lyon", "Marseille", "Train"));
    // catalogueTrajet.Ajouter(new TrajetSimple("Lyon", "Cannes", "Train"));
    // catalogueTrajet.Ajouter(new TrajetSimple("Troucoin", "Cannes", "Train"));
    // catalogueTrajet.Ajouter(new TrajetSimple("Marseille", "Cannes", "Train"));

    // catalogueTrajet.initSearch("Paris", "Cannes");

    return 0;
}