#include <iostream>

template <typename T>
class Maillon
{
public:
    Maillon();
    Maillon(T valeur, Maillon *suivant);
    ~Maillon();

private:
    T valeur;
    Maillon<T> *suivant;
};