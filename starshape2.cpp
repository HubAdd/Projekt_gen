#include "starshape2.h"
#include <cmath>


StarShape2::StarShape2(float radius) {
        type=3;
        setPointCount(48); // 24 ramion, czyli 48 wierzchołków (wewnętrzne i zewnętrzne)
        setRadius(radius);
        setFillColor(sf::Color::Yellow);
    }

void StarShape2::setRadius(float radius) {
        const float PI = 3.14159265358979f;
        float angleStep = PI / 24; // 48 wierzchołków na pełny obrót, co 7.5 stopnia (PI/24 radiana)

        for (size_t i = 0; i < 48; ++i) {
            float angle = i * angleStep;
            float currentRadius = (i % 2 == 0) ? radius : radius / 2.5f; // Ramiona na przemian długie i krótkie
            float x = std::cos(angle) * currentRadius;
            float y = std::sin(angle) * currentRadius;
            setPoint(i, sf::Vector2f(radius + x, radius + y)); // Przesunięcie środka do (radius, radius)
        }
    }

