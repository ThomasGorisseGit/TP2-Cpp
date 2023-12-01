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
Trajet::Trajet(char *DepartVille, char *ArriveeVille) : depart(DepartVille), arrivee(ArriveeVille)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Trajet>" << endl;
#endif
} //----- Fin de Trajet

/*Trajet::Trajet ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Trajet>" << endl;
#endif
} //----- Fin de Trajet*/

Trajet::~Trajet()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Trajet>" << endl;
#endif
} //----- Fin de ~Trajet

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
