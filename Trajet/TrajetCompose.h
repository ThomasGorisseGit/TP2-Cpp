#if !defined(TrajetCompose_H)
#define TrajetCompose_H

#include "../Liste/Liste.h"
#include "Trajet.h"
#include "TrajetSimple.h"


class TrajetCompose : public Trajet
{

public:
    TrajetCompose(Liste<TrajetSimple>  & listeTrajetSimple);
    

    //void Ajouter(const TrajetSimple & trajet);

    void Decompose(Liste<TrajetSimple> & listeTrajetSimple);

    void Afficher() const;


    virtual int GetType() const;
    virtual unsigned int GetTailleTrajet() const;
    Trajet * GetTrajetSimple(unsigned int indice) const;

    virtual ~TrajetCompose();

protected:
    Liste<TrajetSimple> * listeTrajetCompose;
    unsigned int * taille;
};

#endif
