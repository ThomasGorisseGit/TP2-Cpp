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

    void AjouterMulti(TrajetSimple *trajet);
    // Permet d'ajouter un trajet a la liste des trajets Multi, ne peut être que des trajets simples
    // Mode d'emploi :
    //      Appel de la méthode ajouter catalogue.Ajouter(trajet)

    void Afficher(Liste<Trajet> *listeTrajetSimple, Liste<Trajet> *listeTrajetCompose) const;
    // Permet d'afficher le catalogue de trajets (il affcihe d'abord les trajets simples puis les trajets composés)
    // Mode d'emploi :
    //      Appel de la méthode afficher catalogue.Afficher(listeTrajetSimple,listeTrajetCompose)

    //void RechercheAvancee(const char *depart, const char *arrivee);
    // Permet de rechercher de manière approfondie un départ et une arrivée.
    // Le programme va trouver un itinéraire en utilisant sa liste des trajets pour combiner les arrivées et les départs
    // Afin de trouver un trajet permettant de lier départ à arrivee.
    // Mode d'emploi :
    //      Ajouter une liste de trajets au catalogue et entrez : catalogue.RechercheAvancee("depart","arrivee");

    void RechercheAvanceeGabin(const char *depart, const char *arrivee, Liste<TrajetSimple> & itineraires, Liste<TrajetSimple> & itineraireActuel);


    Liste<TrajetSimple> * Rechercher(const char *depart, const char *arrivee, bool verbose) const;
    // Permet au programme de rechercher un trajet qui part d'un départ et arrive à une arrivée.
    // renvoi true si un trajet a été trouvé
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

    void GetTrajetSimpleEtCompose(Liste<Trajet> *listeTrajetSimple, Liste<Trajet> *listeTrajetCompose);
    // Permet de séparer les trajets simples et les trajets composés dans deux listes différentes.
    // Mode d'emploi :
    //      Appel de la méthode catalogue.getTrajetSimpleEtCompose(listeTrajetSimple,listeTrajetCompose)

    void Simplification();
    //Fonction qui prend tous les trajets compose dans la liste et les transforme en trajet simple
    //dans listeTrajetEnSimple

    void TestErase();

protected:
    //Liste<TrajetSimple> *rechercheDepuisDepart(const char *depart, Liste<TrajetSimple> *listeARemplir);
    // Renvoie une liste de trajets qui partent du départ passé en paramètre.
    // Mode d'emploi :
    // Utilisé dans les méthodes permettant une recherche avancee
    // Méthode privée.

    //bool trajetArrivantADestination(Liste<TrajetSimple> *listeTrajetParcourus, const char *arrivee, Liste<TrajetSimple> *listeARemplir);
    // Permet de parcourir récursivement la liste des trajets et de stocker le chemin nécéssaire pour arriver à destination.
    // La liste des trajets nécéssaires est stockée dans listeARemplir.
    // Cette méthode est utilisée dans les méthodes de recherche avancee
    // Méthode privée.

   

    Liste<Trajet> *listeTrajet;
    Liste<TrajetSimple> *listeTrajetEnSimple;
    // Attribut représentant la liste des trajets contenus dans un catalogue.
};

#endif // Catalogue_H
