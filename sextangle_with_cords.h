#ifndef SEXTANGLE_WITH_CORDS_H
#define SEXTANGLE_WITH_CORDS_H

#include "sextangle.h"

class sextangle_with_cords : public sextangle
{
public:
    sextangle_with_cords(sextangle & s, const sf::Vector2i & cords):
        sextangle(s),kords(cords){}
    sf::Vector2i get_kords(){return kords;}
protected:
    sf::Vector2i kords;
};

#endif // SEXTANGLE_WITH_CORDS_H
