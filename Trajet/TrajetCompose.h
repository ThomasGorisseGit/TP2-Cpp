#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H

#include "../Liste/Liste.h"


class TrajetCompose : public Trajet
{

public:


    TrajetCompose (const char * Depart, const char * Arrivee);


    virtual ~TrajetCompose ( );
 

protected:

Liste<TrajetSimple> ListeTrajetComposee;

};

#endif 

