#if !defined(Catalogue_H)
#define Catalogue_H
#include "../Trajet/Trajet.h"
#include "../Liste/Liste.h"
#include "../Trajet/TrajetSimple.h"
#include "../Trajet/TrajetCompose.h"
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

public:
    void Ajouter(Trajet *trajet);
    // Permet d'ajouter un trajet a la liste des trajets proposés dans le catalogue
    // Mode d'emploi :
    //      Appel de la méthode ajouter catalogue.Ajouter(trajet)
    void parse();
    void Afficher();
    // Permet d'afficher tous les trajets contenus dans la liste des trajets proposés.
    // Mode d'emploi :
    //      Appel de la méthode afficher catalogue.Afficher()

    void Rechercher(const char* Depart, const char* Arrivee, Liste<Trajet> & ListeARemplir) const;
    //Fonction qui recherche un trajet dans le catalogue et renvoie une liste des trajets ayant les
    //meme départ et arrivee


    void RechercherTrajet(const char * depart, const char * arrivee) const;

//------------------------------------------------- Surcharge d'opérateurs
    // Mode d'emploi :
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    Catalogue(const Catalogue &unCatalogue);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Catalogue();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Catalogue();
    // Mode d'emploi :
    //
    // Contrat :
    //

protected:
    Liste<Trajet> *listeTrajet;
};

#endif // Catalogue_H
