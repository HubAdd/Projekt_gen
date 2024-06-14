#ifndef HEXAGON_H
#define HEXAGON_H

#include "customshape.h"

//jeden ze znaczków (pomarańczowy sześciokąt)
class Hexagon : public CustomShape {
public:
    // Konstruktor przyjmujący promień jako argument
    Hexagon(float radius);
};

#endif // HEXAGON_H
