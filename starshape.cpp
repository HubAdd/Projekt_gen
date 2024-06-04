#include "starshape.h"
#include <cmath>


StarShape::StarShape(float radius) {
        type=1;
        setPointCount(12);  // 6 ramion, więc 12 wierzchołków (dwa na każde ramię)
        setStarPoints(radius);
        setFillColor(sf::Color::Blue);
    }


    void StarShape::setStarPoints(float radius) {
        float angle = M_PI / 6.0f;  // 30 stopni
        for (int i = 0; i < 12; ++i) {
            float r = (i % 2 == 0) ? radius : radius / 2;
            float x = r * std::cos(i * angle);
            float y = r * std::sin(i * angle);
            setPoint(i, sf::Vector2f(radius + x, radius + y));
        }
    }
