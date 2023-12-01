#include <iostream>
#include <cstring>
#include "Catalogue/Catalogue.h"
#include "Trajet/TrajetSimple.h"
using namespace std;


int main()
{
<<<<<<< HEAD
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
    
=======

    //ratio : conflit by gabin 
    cout << "Hello World!" << endl;
>>>>>>> 0ceb52eb85616a551401e7aceb9e5b830639919a
    return 0;
}