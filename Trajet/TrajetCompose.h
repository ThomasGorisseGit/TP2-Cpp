#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H

#include "liste.h"


class TrajetCompose : public Trajet
{

public:


    TrajetCompose ( );


    virtual ~TrajetCompose ( );
 

protected:

Liste<TrajetSimple> ListeTrajetCompose;

};

#endif 

