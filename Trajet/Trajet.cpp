/*************************************************************************
                           Trajet  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Trajet> (fichier Trajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
char *Trajet::GetDepart() const
{
    return depart;
}

char *Trajet::GetArrivee() const
{
    return arrivee;
}

void Trajet::Afficher() const
{
    cout << "Depart | " << depart << " | \n Arrivee | " << arrivee << " |";
}


//------------------------------------------------- Surcharge d'opérateurs
/*Trajet & Trajet::operator = ( const Trajet & unTrajet )
// Algorithme :
//
{
} //----- Fin de operator =*/

//-------------------------------------------- Constructeurs - destructeur
Trajet::Trajet(const char *DepartVille,const char *ArriveeVille)
{
#ifdef MAP
    cout << "Appel au constructeur de <Trajet>" << endl;
#endif
    depart = new char[strlen(DepartVille)+1];
    strcpy(depart,DepartVille);

    arrivee = new char[strlen(ArriveeVille)+1];
    strcpy(arrivee,ArriveeVille);
} //----- Fin de Trajet

/*Trajet::Trajet ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Trajet>" << endl;
#endif
} //----- Fin de Trajet*/
Trajet::Trajet( const Trajet& ref){
    #ifdef MAP
    cout << "Appel au constructeur de copie de <Trajet>" << endl;
    #endif
    this->depart = new char[strlen(ref.depart)+1];
    this->arrivee = new char[strlen(ref.arrivee)+1];
    strcpy(this->depart,ref.depart);
    strcpy(this->arrivee,ref.arrivee);
    
}
Trajet::~Trajet()
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au destructeur de <Trajet> " ;
        cout << "Destruction de " << depart << " et " << arrivee << endl;
    #endif
    delete[] depart;
    delete[] arrivee;

} //----- Fin de ~Trajet

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
