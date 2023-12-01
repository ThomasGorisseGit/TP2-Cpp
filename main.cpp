#include <iostream>
#include <cstring>
#include "Catalogue/Catalogue.h"
#include "Trajet/Trajet.h"
#include "Trajet/TrajetSimple.h"
#include "Trajet/TrajetCompose.h"
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

    while(true){
        cout << "Que voulez-vous faire ?" << endl;
        cout << "1. Afficher le catalogue" << endl;
        cout << "2. Ajouter un trajet simple" << endl;
        cout << "3. Ajouter un trajet composé" << endl;
        cout << "4. Rechercher un trajet" << endl;
        cout << "5. Quitter" << endl;

        int choix;
        cin >> choix; // Choix de l'utilisateur

        switch (choix)
        {
            case 1:
                catalogueTrajet.Afficher(); // Affichage du catalogue
                break;
            case 2:
                cout << "Voulez vous rentrer un trajet simple ou un trajet composée ?" << endl;
                cout << "1. Trajet simple" << endl;
                cout << "2. Trajet composé" << endl;
                int choixTrajet;
                cin >> choixTrajet; // Choix de l'utilisateur

                // Ajout d'un trajet simple
                if(choixTrajet == 1){
                    // Ajout d'un trajet simple
                    char* depart;
                    char* arrivee;
                    char* moyenTransport;

                    cout << "Veuillez rentrer le départ du trajet : " << endl;
                    cin >> depart;
                    cout << "Veuillez rentrer l'arrivée du trajet : " << endl;
                    cin >> arrivee;
                    cout << "Veuillez rentrer le moyen de transport du trajet : " << endl;
                    cin >> moyenTransport;

                    TrajetSimple trajetSimple(depart, arrivee, moyenTransport);  // Création du trajet simple    
                    catalogueTrajet.AjouterTrajet(&trajetSimple); // Ajout du trajet simple au catalogue
                    cout << "Fin de la création du trajet simple" << endl;

                } else if(choixTrajet == 2){
                    
                    // Ajout d'un trajet composé
                    bool isFirstEtape = true;
                    char * departTrajetCompose;
                    char * arriveeTrajetCompose;

                    Liste<TrajetSimple> listeTrajetSimple;
                    cout << "Veuillez rentrer le départ du trajet composé : " << endl;
                    cin >> departTrajetCompose;
                    cout << "Veuillez rentrer l'arrivée du trajet composé : " << endl;
                    cin >> arriveeTrajetCompose;


                    do{
                        char * departTrajetSimple;

                        // Si on ajoute le premier trajet simple, on récupère le départ du trajet composé
                        if (isFirstEtape){
                            strcpy(departTrajetSimple, departTrajetCompose);
                            isFirstEtape = false;
                        } else {
                            strcpy(departTrajetSimple, arriveeTrajetCompose);
                        }

                        static char * arriveTrajetSimple;
                        cout<< "Veuillez rentrer l'arrivée du trajet simple : " << endl;
                        cin >> arriveTrajetSimple;
                        char * moyenTransportTrajetSimple;
                        cout<< "Veuillez rentrer le moyen de transport du trajet simple : " << endl;
                        cin >> moyenTransportTrajetSimple;

                        TrajetSimple trajetSimple(departTrajetSimple, arriveTrajetSimple, moyenTransportTrajetSimple);
                        listeTrajetSimple.Ajouter(trajetSimple);
                        
                    }while(strcmp(arriveTrajetSimple, arriveeTrajetCompose) != 0);

                    cout << "Fin de la création du trajet composé" << endl;
                

                } else {
                    // Choix de l'utilisateur invalide
                    cout << "Erreur, veuillez rentrer un choix valide" << endl;
                }
                break;
    }

    return 0;
}