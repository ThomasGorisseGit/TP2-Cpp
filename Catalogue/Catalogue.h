#if !defined(Catalogue_H)
#define Catalogue_H

#include "../Trajet/Trajet.h"
#include "../Liste/Liste.h"
#include "../Trajet/TrajetSimple.h"
#include "../Trajet/TrajetCompose.h"

class Catalogue
{

public:
    Catalogue();
    // Constructeur de la classe Catalogue. Création d'un catalogue vide.

    Catalogue(const Catalogue &unCatalogue);
    // Constructeur de copie d'un catalogue. Il recopie tous les trajets du catalogue passé en paramètre.

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

    Liste<TrajetSimple> *Rechercher(const char *depart, const char *arrivee) const;
    // Permet au programme de rechercher un trajet qui part d'un départ et arrive à une arrivée.
    // La méthode renvoie une liste de trajets simples qui permettent d'aller du point A au point B.
    // Mode d'emploi :
    //      Ajouter une liste de trajets (simples) au catalogue et entrez : catalogue.Rechercher("depart","arrivee", verbose);

    void RechercheAvancee(const char *depart, const char *arrivee, Liste<TrajetSimple> &itineraires, Liste<TrajetSimple> &itineraireActuel);
    // Permet de rechercher de manière complexe un trajet et d'afficher tous les trajets possibles pour aller d'un point A à un point B.
    // La méthode est récursive et permet de trouver tous les trajets possibles pour aller d'un point A à un point B.
    // Mode d'emploi :
    //      Ajouter une liste de trajets au catalogue et entrez : catalogue.RechercheAvancee("depart","arrivee", itineraires, itineraireActuel);

    void GetTrajetSimpleEtCompose(Liste<Trajet> *listeTrajetSimple, Liste<Trajet> *listeTrajetCompose);
    // Permet de séparer les trajets simples et les trajets composés dans deux listes différentes.
    // La méthode remplie les deux listes passées en paramètre.
    // Mode d'emploi :
    //      Appel de la méthode catalogue.getTrajetSimpleEtCompose(listeTrajetSimple,listeTrajetCompose)

    void Simplification();
    // Fonction qui prend tous les trajets composés et les transforme en trajets simples.
    // Mode d'emploi :
    //      Appel de la méthode catalogue.Simplification()

    virtual ~Catalogue();
    // Détruit l'objet catalogue en assurant une destruction totale de chaque trajet contenus dans le catalogue.

protected:
    Liste<Trajet> *listeTrajet;
    Liste<TrajetSimple> *listeTrajetEnSimple;
};

#endif // Catalogue_H
