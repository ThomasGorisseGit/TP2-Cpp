/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( Catalogue_H )
#define Catalogue_H
#include "../Trajet/Trajet.h"
#include "../Liste/Liste.h"
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
//
//
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


    void Ajouter(const Trajet & trajet);
    // Permet d'ajouter un trajet a la liste des trajets proposés dans le catalogue
    // Mode d'emploi :
    //      Appel de la méthode ajouter catalogue.Ajouter(trajet)

    void Afficher();
    // Permet d'afficher tous les trajets contenus dans la liste des trajets proposés.
    // Mode d'emploi :
    //      Appel de la méthode afficher catalogue.Afficher()


//------------------------------------------------- Surcharge d'opérateurs
    Catalogue & operator = ( const Catalogue & unCatalogue );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Catalogue ( const Catalogue & unCatalogue );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Catalogue ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Catalogue ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés


// Un catalogue possède une liste de trajets (Composés et simples)

Liste<Trajet>* listeTrajet;
};

//-------------------------------- Autres définitions dépendantes de <Catalogue>

#endif // Catalogue_H

