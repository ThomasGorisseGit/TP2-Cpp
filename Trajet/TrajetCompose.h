#if !defined(TrajetCompose_H)
#define TrajetCompose_H

#include "../Liste/Liste.h"
#include "Trajet.h"
#include "TrajetSimple.h"

class TrajetCompose : public Trajet
{

public:
    TrajetCompose(const Liste<TrajetSimple> & listeTrajetSimple);

    //void Ajouter(const TrajetSimple & trajet);

    void Afficher() const;

    virtual ~TrajetCompose();

protected:
    const Liste<TrajetSimple> & ListeTrajetCompose;
    unsigned int taille = 0;
};

#endif
