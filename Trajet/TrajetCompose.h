#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H


class TrajetCompose : public Trajet
{

public:

    TrajetCompose & operator = ( const TrajetCompose & unTrajetCompose );
 
    TrajetCompose ( const TrajetCompose & unTrajetCompose );

    TrajetCompose ( );


    virtual ~TrajetCompose ( );
 

protected:
};

#endif 

