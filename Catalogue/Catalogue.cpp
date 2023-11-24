/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "../Liste/Liste.h"
#include "../Trajet/Trajet.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques



//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ( const Catalogue & unCatalogue )
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue (constructeur de copie)


Catalogue::Catalogue ( )
{
    #ifdef MAP
        cout << "Appel au constructeur de <Catalogue>" << endl;
    #endif

    this->listeTrajet = new Liste();

} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
{
    #ifdef MAP
        cout << "Appel au destructeur de <Catalogue>" << endl;
    #endif

    delete this->listeTrajet;
} //----- Fin de ~Catalogue

void Catalogue::Ajouter(const Trajet & trajet){
    this->listeTrajet.ajouter(trajet);
}

void Catalogue::Afficher() {
    cout << "-----------------------------------------------------------------" <<endl;
    cout << "---------------------------BIENVENUE-----------------------------" <<endl;
    cout << "---------------------------SUR    LE-----------------------------" <<endl;
    cout << "---------------------------CATALOGUE-----------------------------" <<endl;
    cout << "-----------------------------------------------------------------" <<endl;

}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

