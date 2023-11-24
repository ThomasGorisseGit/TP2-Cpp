#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H

#include "../Liste/Liste.h"
#include "Trajet.h"
#include "TrajetSimple.h"


class TrajetCompose : public Trajet
{

public:


    TrajetCompose (const Liste<TrajetSimple>);

    void Ajouter (const TrajetSimple &trajet);

    void Afficher() const;


    virtual ~TrajetCompose ( );
 

protected:

    Liste<TrajetSimple> ListeTrajetCompose;

};

#endif 

