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
    delete [] this->listeTrajet;
    this->listeTrajet = malloc(sizeof(Trajet) * unCatalogue.listeTrajet->GetTaille());

    for(int i = 0 ; i<unCatalogue.listeTrajet.GetTaille(); i ++){
        this->listeTrajet->Ajouter(
                unCatalogue.listeTrajet->GetValeur(i);
                )
    }
} //----- Fin de Catalogue (constructeur de copie)


Catalogue::Catalogue ( )
{
    #ifdef MAP
        cout << "Appel au constructeur de <Catalogue>" << endl;
    #endif

} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
{
    #ifdef MAP
        cout << "Appel au destructeur de <Catalogue>" << endl;
    #endif
} //----- Fin de ~Catalogue

void Catalogue::Ajouter(const Trajet & trajet){
    this->listeTrajet.Ajouter(trajet);
}

void Catalogue::Afficher() {
    cout << "-----------------------------------------------------------------" <<endl;
    cout << "---------------------------BIENVENUE-----------------------------" <<endl;
    cout << "---------------------------SUR    LE-----------------------------" <<endl;
    cout << "---------------------------CATALOGUE-----------------------------" <<endl;
    cout << "-----------------------------------------------------------------" <<endl;
    int i =0;
    while( i<this->listeTrajet.GetTaille() ){
        this->listeTrajet.GetValeur(i).Afficher();
    }
}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

