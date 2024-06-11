#ifndef ROUND_COUNTER_H
#define ROUND_COUNTER_H
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "texture_pack.h"


class Round_Counter : public sf::Drawable
{
public:
    Round_Counter(sf::Texture & t);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;
    unsigned int get_round();
    void add_round(const unsigned int &p_num, Texture_pack & t);

private:
    sf::Sprite sprite;
    unsigned int round;
};

#endif // ROUND_COUNTER_H
