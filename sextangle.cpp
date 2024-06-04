#include "sextangle.h"
#include <cmath>

sextangle::sextangle(const float &size):
    sf::ConvexShape(){

    setPointCount(6);
    h=sqrt(3)*size/2;
    const float a=size/2;
    setPoint(0, {2*a,0});
    setPoint(1, {a,h});
    setPoint(2, {-a,h});
    setPoint(3, {-2*a,0});
    setPoint(4, {-a,-h});
    setPoint(5, {a,-h});
}
bool sextangle::vec_on (const sf::Vector2i &vec)
{
    // Pobranie pozycji środka koła
    sf::Vector2f circleCenter = getPosition();

    // Pobranie promienia koła
    float radius = h;

    // Obliczenie odległości między pozycją kursora a środkiem koła
    float distance = std::sqrt(std::pow(vec.x - circleCenter.x, 2) + std::pow(vec.y - circleCenter.y, 2));

    // Sprawdzenie, czy odległość jest mniejsza lub równa promieniowi koła
    return distance <= radius;
}
bool sextangle::mouse_on (const sf::RenderWindow & window)
{
    // Pobranie pozycji kursora względem okna
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    return vec_on(mousePos);
}
