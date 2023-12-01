#include "Trajet.h"
#if !defined(TrajetSimple_H)
#define TrajetSimple_H

class TrajetSimple : public Trajet
{

public:
    TrajetSimple(char *depart, char *arrivee);
    virtual ~TrajetSimple();
};

#endif