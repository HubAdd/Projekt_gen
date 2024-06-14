#ifndef STARSHAPE1_H
#define STARSHAPE1_H

#include "customshape.h"

//jeden ze znaczków (czerwona gwiazda)
class StarShape1 : public CustomShape {
public:
    StarShape1(float radius);

    void setRadius(float radius);
};

#endif // STARSHAPE1_H
