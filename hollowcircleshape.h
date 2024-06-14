#ifndef HOLLOWCIRCLESHAPE_H
#define HOLLOWCIRCLESHAPE_H

#include "customshape.h"

//jeden ze znaczków (fioletowy okrąg)
class HollowCircleShape : public CustomShape {
public:
    //konstruktor przyjmuje promień i liczbę pkt, kora domyślnie jest ustawiona na 100
    HollowCircleShape(float radius, size_t pointCount = 100);

    //ustawienie promienia
    void setRadius(float radius);

    //zwracanie promienia
    float getRadius() const;

private:
    float radius;

    void updatePoints();
};

#endif // HOLLOWCIRCLESHAPE_H
