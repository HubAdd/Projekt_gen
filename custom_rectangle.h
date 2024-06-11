#ifndef CUSTOM_RECTANGLE_H
#define CUSTOM_RECTANGLE_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Time.hpp"
class custom_rectangle: public sf::RectangleShape
{
public:
    custom_rectangle(const sf::Vector2f & pos,const sf::Vector2f & size);
    custom_rectangle();
    void set_speed(const int & x,const int & y,const int & z);
    void set_bounds(const int & a,const int & b,const int & c,const int & d);
    void bounce();
    void animate(const sf::Time &elapsed);

private:
    int speed_x=0;
    int speed_y=0;
    int speed_rotation=0;
    std::pair <int,int> x_bounds;
    std::pair <int,int> y_bounds;

};

#endif // CUSTOM_RECTANGLE_H
