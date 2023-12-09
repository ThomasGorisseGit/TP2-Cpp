/*************************************************************************
                        Trajet  -  description
                            -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if !defined(Trajet_H)
#define Trajet_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
//
//
//------------------------------------------------------------------------

class Trajet
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    
    // Méthode de type Get
    // Elle permet d'accéder au départ d'un trajet.
    char *GetDepart() const;

    // Méthode de type Get
    //  Elle permet d'accéder à l'arrivée d'un trajet.
    char *GetArrivee() const; // getteur de l'arrivée

    //Liste<TrajetSimple> & Rechercher(const char* Depart, const char* Arrivee) const;

    // Méthode de type affichage
    // Elle permet d'afficher les attributs d'un trajet.
    // Notamment le départ et l'arrivée.
    // L'affichage est élaboré.
    virtual void Afficher() const;

    //------------------------------------------------- Surcharge d'opérateurs
    // Trajet & operator = ( const Trajet & unTrajet );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    // Trajet ( const Trajet & unTrajet );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Trajet(const char *DepartVille, const char *ArrivéeVille);
    // Mode d'emploi :
    //
    // Contrat :
    //

    Trajet( const Trajet& ref);

    virtual unsigned int GetTailleTrajet() const; //renvoi 0 si appelé sur un Trajet (ni simple ni compose)

    virtual Trajet * GetTrajetSimple(unsigned int indice) const; //renvoi nullptr si appellé sur un Trajet (ni simple ni compose)


    virtual int GetType() const;
    virtual char *GetTransport() const;
   


    virtual ~Trajet();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    char *depart;
    char *arrivee;
    enum typeTrajet  {SansType = 0, Simple = 1, Compose = 2}; //SansType = Appel de GetType sur un Trajet (ni simple ni compose)
    
};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif // Trajet_H
