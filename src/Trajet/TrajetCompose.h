#if !defined(TrajetCompose_H)
#define TrajetCompose_H

#include "../Liste/Liste.h"
#include "Trajet.h"
#include "TrajetSimple.h"

class TrajetCompose : public Trajet
{

public:
    TrajetCompose(Liste<TrajetSimple> &listeTrajetSimple);
    // Constructeur de la classe TrajetCompose
    // Il prend en paramètre une liste de trajets simples
    // Mode d'emploi :
    //       Appel du constructeur avec TrajetCompose trajet(listeTrajetSimple);

    void Decompose(Liste<TrajetSimple> &listeTrajetSimple);
    // Méthode permettant de décomposer un trajet composé en une liste de trajets simples
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.Decompose(listeTrajetSimple);

    void Afficher() const;
    // Méthode permettant d'afficher un trajet composé.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.Afficher();

    inline virtual int GetType() const { return Compose; }
    // Méthode permettant d'accéder au type d'un trajet composé.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetType();

    inline virtual unsigned int GetTailleTrajet() const { return *taille; }
    // Méthode permettant d'accéder à la taille d'un trajet composé.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetTailleTrajet();

    inline Trajet *GetTrajetSimple(unsigned int indice) const { return listeTrajetCompose->GetValeur(indice); }
    // Méthode permettant d'accéder au trajet simple d'un indice donné du trajet composé.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetTrajetSimple(indice);

    virtual ~TrajetCompose();
    // Destructeur de la classe TrajetCompose

protected:
    Liste<TrajetSimple> *listeTrajetCompose;
    unsigned int *taille;
};

#endif // TrajetCompose_H
