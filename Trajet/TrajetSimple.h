#include "Trajet.h"
#if !defined(TrajetSimple_H)
#define TrajetSimple_H

class TrajetSimple : public Trajet
{

public:
    TrajetSimple(const char *Depart, const char *Arrivee, char *M_transport);
    // Constructeur de la classe TrajetSimple
    // Il prend en paramètre le départ, l'arrivée et le transport du trajet
    // Mode d'emploi :
    //       Appel du constructeur avec TrajetSimple trajet(Depart, Arrivee, M_transport);

    TrajetSimple(const Trajet &ref, char *trans);
    // Constructeur de copie de la classe TrajetSimple
    // Il prend en paramètre une référence vers un trajet et un transport
    // Mode d'emploi :
    //       Appel du constructeur avec TrajetSimple trajet(_trajet, monTransport);

    inline char *GetTransport() const { return transport; }
    // Méthode permettant d'accéder au transport d'un trajet simple.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetTransport();

    void Afficher() const;
    // Méthode permettant d'afficher un trajet simple.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.Afficher();

    void AfficherPetit() const;
    // Méthode permettant d'afficher un trajet simple de manière réduite.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.AfficherPetit();
    

    inline virtual unsigned int GetTailleTrajet() const { return 1; }
    // Méthode permettant d'accéder à la taille d'un trajet simple.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetTailleTrajet();

    inline virtual int GetType() const { return Simple; }
    // Méthode permettant d'accéder au type d'un trajet simple.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetType();

    virtual ~TrajetSimple();
    // Destructeur de la classe TrajetSimple

protected:
    // Un trajet simple n'est défini que par son moyen de transport
    char *transport;
};
#endif // TrajetSimple_H