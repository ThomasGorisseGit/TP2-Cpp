#include "Trajet.h"
#if !defined(TrajetSimple_H)
#define TrajetSimple_H

class TrajetSimple : public Trajet
{

public:
    TrajetSimple(const char *Depart, const char *Arrivee, const char * M_transport);
    void Afficher() const;
    void AfficherPetit() const;
    virtual ~TrajetSimple();


protected :
    char * transport;
};

#endif