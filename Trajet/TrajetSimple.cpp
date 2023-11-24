#include <iostream>
using namespace std;
#include "TrajetSimple.h"






TrajetSimple::TrajetSimple ( )

{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
} 


TrajetSimple::~TrajetSimple ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
} s

