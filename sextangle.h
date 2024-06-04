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
    float h_(){return h;}
    friend class Token;
protected:
    float h;
};

#endif // SEXTANGLE_H
