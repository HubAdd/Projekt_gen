#ifndef SEXTANGLE_H
#define SEXTANGLE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class sextangle : public sf::ConvexShape
{
public:
    sextangle(const float &size);
    bool mouse_on (const sf::RenderWindow & window);
    bool vec_on (const sf::Vector2i &vec);
    float h_();
    friend class Token;

};

#endif // SEXTANGLE_H
