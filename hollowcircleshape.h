#ifndef HOLLOWCIRCLESHAPE_H
#define HOLLOWCIRCLESHAPE_H

#include "customshape.h"

class HollowCircleShape : public CustomShape {
public:
    HollowCircleShape(float radius, size_t pointCount = 100);

    void setRadius(float radius);

    float getRadius() const;

private:
    float radius;

    void updatePoints();
};

#endif // HOLLOWCIRCLESHAPE_H
