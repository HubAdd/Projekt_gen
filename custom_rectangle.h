#ifndef CUSTOM_RECTANGLE_H
#define CUSTOM_RECTANGLE_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Time.hpp"

//klasa custom rectangle nie zawiera się wyjątkowo w Engine, tylko jest wykorzystywana jako konfetii w animacji zwyciężcy
class custom_rectangle: public sf::RectangleShape
{
public:
    //kostruktor przyjmujący pozycje i wielkość
    custom_rectangle(const sf::Vector2f & pos,const sf::Vector2f & size);

    //domyślny konstruktor
    custom_rectangle();

    //ustawienie szybkości danego prostokąta
    void set_speed(const int & x,const int & y,const int & z);

    //ustawienie granic danego prostokąta
    void set_bounds(const int & a,const int & b,const int & c,const int & d);

    //funkcja która w przypadku wylotu poza okno odbija prostokąt
    void bounce();

    //funckja która dokonuje animacjii prostokąta i przyjmuje czas jako argument by go odpowiednio przesunąć
    void animate(const sf::Time &elapsed);

private:
    //prędkości na danych osiach (mogą być ujemne)
    int speed_x=0;
    int speed_y=0;
    int speed_rotation=0;

    //granice obszaru
    std::pair <int,int> x_bounds;
    std::pair <int,int> y_bounds;

};

#endif // CUSTOM_RECTANGLE_H
