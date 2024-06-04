#include "starshape1.h"
#include <cmath>


StarShape1::StarShape1(float radius) {
        type=2;
        setPointCount(24); // 12 ramion, czyli 24 wierzchołki (wewnętrzne i zewnętrzne)
        setRadius(radius);
        setFillColor(sf::Color::Red);
    }

    void StarShape1::setRadius(float radius) {
        const float PI = 3.14159265358979f;
        float angleStep = PI / 12; // 24 wierzchołki na pełny obrót, co 15 stopni (PI/12 radiana)

        for (size_t i = 0; i < 24; ++i) {
            float angle = i * angleStep;
            float currentRadius = (i % 2 == 0) ? radius : radius / 2.5f; // Ramiona na przemian długie i krótkie
            float x = std::cos(angle) * currentRadius;
            float y = std::sin(angle) * currentRadius;
            setPoint(i, sf::Vector2f(radius + x, radius + y)); // Przesunięcie środka do (radius, radius)
        }
    }

