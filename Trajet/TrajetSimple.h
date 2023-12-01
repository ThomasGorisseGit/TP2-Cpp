#include "Trajet.h"
#if !defined(TrajetSimple_H)
#define TrajetSimple_H

class TrajetSimple : public Trajet
{

public:
    TrajetSimple(char *Depart, char *Arrivee,char * M_transport);
    void Afficher() const;
    void AfficherPetit() const;
    virtual ~TrajetSimple();


protected :
    char * transport;
};

#endif