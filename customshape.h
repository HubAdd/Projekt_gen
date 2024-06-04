#ifndef CUSTOMSHAPE_H
#define CUSTOMSHAPE_H

#include "SFML/Graphics/ConvexShape.hpp"
class CustomShape: public sf::ConvexShape
{
public:
    unsigned int get_type (){return type;};
protected:
    unsigned int type;
};

#endif // CUSTOMSHAPE_H
