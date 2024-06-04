#include "hexagon.h"
#include <cmath>
Hexagon::Hexagon(float radius)
{
    type=5;
    // Ustawienie liczby punktów na 6 (sześciokąt)
    setPointCount(6);

    // Obliczenie i ustawienie punktów
    for (int i = 0; i < 6; ++i) {
        float angle = i * 60 * M_PI / 180;  // Konwersja stopni na radiany
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        setPoint(i, sf::Vector2f(x, y));
    }

    // Ustawienie koloru na pomarańczowy
    setFillColor(sf::Color(255, 165, 0));  // Pomarańczowy
}
