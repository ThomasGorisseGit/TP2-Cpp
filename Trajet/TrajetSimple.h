#include "Trajet.h"
#if !defined(TrajetSimple_H)
#define TrajetSimple_H

class TrajetSimple : public Trajet
{

public:
<<<<<<< HEAD
    TrajetSimple(char *Depart, char *Arrivee,char * M_transport);
    TrajetSimple( const TrajetSimple& ref);
=======
    TrajetSimple(const char *Depart, const char *Arrivee, const char * M_transport);
>>>>>>> 0ceb52eb85616a551401e7aceb9e5b830639919a
    void Afficher() const;
    void AfficherPetit() const;
    virtual ~TrajetSimple();


protected :
    char * transport;
};

#endif