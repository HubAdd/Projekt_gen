#include "custom_rectangle.h"

custom_rectangle::custom_rectangle(const sf::Vector2f & pos,const sf::Vector2f & size):
    sf::RectangleShape(size){setPosition(pos);}
custom_rectangle::custom_rectangle():
    sf::RectangleShape({static_cast<float>(rand()%30+1), static_cast<float>(rand()%30+1)}){}
void custom_rectangle::set_speed(const int & x,const int & y,const int & z)
{
    speed_x=x;
    speed_y=y;
    speed_rotation=z;
}
void custom_rectangle::set_bounds(const int & a,const int & b,const int & c,const int & d)
{
    x_bounds.first=a;
    x_bounds.second=b;
    y_bounds.first=c;
    y_bounds.second=d;
}
void custom_rectangle::bounce()
{
    auto lim=getGlobalBounds();
    auto abs=[](int a){if(a>=0){return a;}else{return -a;};};
    if(lim.left<=x_bounds.first)
    {
        speed_x=abs(speed_x);

    }
    if(lim.left+lim.width>=x_bounds.second)
    {
        speed_x=-abs(speed_x);

    }
    if(lim.top<=y_bounds.first)
    {
        speed_y=abs(speed_y);

    }
    if(lim.top+lim.height>=y_bounds.second)
    {
        speed_y=-abs(speed_y);

    }

}
void custom_rectangle::animate(const sf::Time &elapsed)
{


    move(speed_x*elapsed.asSeconds(),speed_y*elapsed.asSeconds());
    rotate(speed_rotation*elapsed.asSeconds());
    bounce();


}

