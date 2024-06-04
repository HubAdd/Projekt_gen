#include "hollowcircleshape.h"
#include <cmath>


HollowCircleShape::HollowCircleShape(float radius, size_t pointCount) {
        type=4;
        setPointCount(pointCount);
        setRadius(radius);
        setOutlineColor(sf::Color::Magenta);
        setOutlineThickness(3.f);
        setFillColor(sf::Color::Transparent);
    }

    void HollowCircleShape::setRadius(float radius) {
        this->radius = radius;
        updatePoints();
    }

    float HollowCircleShape::getRadius() const {
        return radius;
    }




    void HollowCircleShape::updatePoints() {
        const float PI = 3.14159265358979f;
        size_t pointCount = getPointCount();
        for (size_t i = 0; i < pointCount; ++i) {
            float angle = i * 2 * PI / pointCount - PI / 2;
            float x = radius * std::cos(angle);
            float y = radius * std::sin(angle);
            setPoint(i, sf::Vector2f(radius + x, radius + y));
        }
    }

