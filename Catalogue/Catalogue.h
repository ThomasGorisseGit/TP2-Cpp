#if !defined(Catalogue_H)
#define Catalogue_H
//--------------------------------------------------- Interfaces utilisées

#include "../Trajet/Trajet.h"
#include "../Liste/Liste.h"
#include "../Trajet/TrajetSimple.h"
#include "../Trajet/TrajetCompose.h"


//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
//      Gestion avancée d'une liste de trajets.
//
//------------------------------------------------------------------------

class Catalogue
{

public:


    void Ajouter(Trajet *trajet);
    // Permet d'ajouter un trajet a la liste des trajets proposés dans le catalogue
    // Mode d'emploi :
    //      Appel de la méthode ajouter catalogue.Ajouter(trajet)



    void Afficher();
    // Permet d'afficher tous les trajets qui sont dans le catalogue, avec un affichage sophistiqué 
    // Mode d'emploi :
    //      Appel de la méthode catalogue.Afficher()


    void RechercheAvancee(const char *depart, const char *arrivee);
    // Permet de rechercher de manière approfondie un départ et une arrivée.
    // Le programme va trouver un itinéraire en utilisant sa liste des trajets pour combiner les arrivées et les départs
    // Afin de trouver un trajet permettant de lier départ à arrivee.
    // Mode d'emploi :
    //      Ajouter une liste de trajets au catalogue et entrez : catalogue.RechercheAvancee("depart","arrivee");


    void Rechercher(const char *depart, const char *arrivee, Liste<Trajet> &ListeARemplir) const;
    // Permet au programme de rechercher un trajet qui part d'un départ et arrive à une arrivée. 
    // Le catalogue renverra la liste des trajets qui font exactement cet itinéraire.
    // Il ne permettera pas de changer de Trajet pour combiner des possibilitées.

    

    //-------------------------------------------- Constructeurs - destructeur
    Catalogue(const Catalogue &unCatalogue);
    // Mode d'emploi (constructeur de copie) :
    // Copie en profondeur d'un catalogue. Il recopie tous les trajets du catalogue passé en paramètres
    
    

    Catalogue();
    // Mode d'emploi :
    // Construit un catalogue composé d'une liste de trajet vide. 
    // Il faut ensuite ajouter des trajets grâce à la méthode Ajouter(trajet)
  

    virtual ~Catalogue();
    // Mode d'emploi :
    // Détruit l'objet catalogue en assurant une destruction totale de chaque trajet contenus dans le catalogue.

protected:

    Liste<Trajet> *rechercheDepuisDepart(const char *depart);
    // Renvoie une liste de trajets qui partent du départ passé en paramètre.
    // Mode d'emploi : 
    // Utilisé dans les méthodes permettant une recherche avancee
    // Méthode privée.


    bool trajetArrivantADestination(Liste<Trajet> *listeTrajetParcourus, const char *arrivee, Liste<Trajet> *listeARemplir);
    // Permet de parcourir récursivement la liste des trajets et de stocker le chemin nécéssaire pour arriver à destination.
    // La liste des trajets nécéssaires est stockée dans listeARemplir.
    // Cette méthode est utilisée dans les méthodes de recherche avancee
    // Méthode privée.


    Liste<Trajet> *listeTrajet;
    // Attribut représentant la liste des trajets contenus dans un catalogue.
};

#endif // Catalogue_H
