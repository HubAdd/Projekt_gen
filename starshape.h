#ifndef STARSHAPE_H
#define STARSHAPE_H

#include "customshape.h"

class StarShape : public CustomShape {
public:
    StarShape(float radius);

private:
    void setStarPoints(float radius);
};

#endif // STARSHAPE_H
