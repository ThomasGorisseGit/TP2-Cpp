#include <iostream>
#include <cstring>
#include "Catalogue/Catalogue.h"
#include "Trajet/TrajetSimple.h"
using namespace std;


int main()
{
    Catalogue catalogue;
    catalogue.Afficher();

    char * depart = new char[10];
    char * arrivee = new char[10];
    char * transport = new char[10];

    strcpy(depart, "Paris");
    strcpy(arrivee, "Lyon");
    strcpy(transport, "Train");

    TrajetSimple trajetSimple(depart, arrivee, transport);

    catalogue.Ajouter(trajetSimple);

    catalogue.Afficher();
    
    return 0;
}