#if !defined(Trajet_H)
#define Trajet_H

class Trajet
{
public:
    Trajet(const char *DepartVille, const char *ArrivéeVille);
    // Constructeur de la classe Trajet
    // Il prend en paramètre le départ et l'arrivée du trajet
    // Mode d'emploi :
    //       Appel du constructeur avec Trajet trajet(DepartVille, ArrivéeVille);

    char *GetDepart() const {return depart;}
    // Méthode permettant d'accéder au départ d'un trajet.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetDepart();

    char *GetArrivee() const {return arrivee;}
    // Méthode permettant d'accéder à l'arrivée d'un trajet.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetArrivee();

    inline virtual void Afficher() const {};
    // Méthode permettant d'afficher un trajet.
    // Si cette méthode est appellée sur un trajet (ni simple ni compose), elle ne fait rien.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.Afficher();

    Trajet(const Trajet &ref);
    // Constructeur de copie de la classe Trajet
    // Il prend en paramètre une référence vers un trajet
    // Mode d'emploi :
    //       Appel du constructeur avec Trajet trajet(_trajet);

    inline virtual unsigned int GetTailleTrajet() const {return 0;}
    // Méthode permettant d'accéder à la taille d'un trajet.
    // Si cette méthode est appellée sur un trajet (ni simple ni compose), elle renvoi 0.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetTailleTrajet();

    inline virtual Trajet *GetTrajetSimple(unsigned int indice) const  {return nullptr;} 
   

    // Méthode permettant d'accéder au trajet simple à l'indice passé en paramètre d'un trajet composé.
    // Si cette méthode est appellée sur un trajet (ni simple ni compose), elle renvoi nullptr.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetTrajetSimple(indice);
    

    inline virtual int GetType() const {return SansType;}
    // Méthode permettant d'accéder au type d'un trajet.
    // Si cette méthode est appellée sur un trajet (ni simple ni compose), elle renvoi 0.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetType();

    inline virtual char *GetTransport() const {return nullptr; }
    // Méthode permettant d'accéder au transport d'un trajet.
    // Si cette méthode est appellée sur un trajet (ni simple ni compose), elle renvoi nullptr.
    // Mode d'emploi :
    //       Appel de la méthode avec trajet.GetTransport();

    virtual ~Trajet();
    // Destructeur de la classe Trajet

protected:
    char *depart;
    char *arrivee;
    enum typeTrajet
    {
        SansType = 0,
        Simple = 1,
        Compose = 2
    }; // SansType = Appel de GetType sur un Trajet (ni simple ni compose)
};
#endif // Trajet_H
