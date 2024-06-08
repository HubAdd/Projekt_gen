#ifndef ROUND_COUNTER_H
#define ROUND_COUNTER_H
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"


class Round_Counter : public sf::Drawable
{
public:
    Round_Counter();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;
    unsigned int get_round();
    void add_round(const unsigned int &p_num);

private:
    sf::RectangleShape rec;
    unsigned int round;
};

#endif // ROUND_COUNTER_H
