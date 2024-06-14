#ifndef CUSTOMSHAPE_H
#define CUSTOMSHAPE_H

#include "SFML/Graphics/ConvexShape.hpp"

//Klasa z której dziedziczą znaczki na tokenach
class CustomShape: public sf::ConvexShape
{
public:
    //funkcja zwracająca liczbe od 1 do 6 oznaczającą typ danego znaczka
    unsigned int get_type (){return type;};
protected:

    //liczba od 1 do 6 oznaczającą typ danego znaczka
    unsigned int type;
};

#endif // CUSTOMSHAPE_H
