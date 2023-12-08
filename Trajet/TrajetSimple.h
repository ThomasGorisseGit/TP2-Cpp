#include "Trajet.h"
#if !defined(TrajetSimple_H)
#define TrajetSimple_H

class TrajetSimple : public Trajet
{

public:
    TrajetSimple(const char *Depart, const char *Arrivee, char *M_transport);
    TrajetSimple(const TrajetSimple &ref);
    char *GetTransport() const;
    void Afficher() const;
    void AfficherPetit() const;

    virtual unsigned int GetTailleTrajet() const;
    virtual int GetType() const;
    

    virtual ~TrajetSimple();

protected:
    char *transport;
};

#endif