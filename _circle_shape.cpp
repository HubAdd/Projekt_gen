#include "_circle_shape.h"
#include <cmath>

_Circle_Shape::_Circle_Shape(float radius, unsigned int pointCount) {
    type=6;
    // Ustawienie liczby punktów
    setPointCount(pointCount);

    // Obliczenie i ustawienie punktów
    for (unsigned int i = 0; i < pointCount; ++i) {
        float angle = i * 2 * M_PI / pointCount;  // Kąt w radianach
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        setPoint(i, sf::Vector2f(x, y));
    }

    // Ustawienie koloru na zielony
    setFillColor(sf::Color::Green);
}

