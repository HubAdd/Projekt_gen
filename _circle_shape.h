#ifndef _CIRCLE_SHAPE_H
#define _CIRCLE_SHAPE_H

#include "customshape.h"

class _Circle_Shape : public CustomShape {
public:
    // Konstruktor przyjmujący promień jako argument
    _Circle_Shape(float radius, unsigned int pointCount = 100);
};

#endif // _CIRCLE_SHAPE_H
