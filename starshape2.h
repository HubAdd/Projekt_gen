#ifndef STARSHAPE2_H
#define STARSHAPE2_H

#include "customshape.h"

class StarShape2 : public CustomShape {
public:
    StarShape2(float radius);

    void setRadius(float radius);
};

#endif // STARSHAPE2_H
