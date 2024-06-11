#include "round_counter.h"
#include "SFML/Graphics/RenderTarget.hpp"


Round_Counter::Round_Counter(sf::Texture & t):sf::Drawable()
{
    round=1;
    sprite.setTexture(t);
    sprite.setPosition(170,40);
    sprite.setScale(0.8f,0.8f);
}



unsigned int Round_Counter::get_round(){return round;}

void Round_Counter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite , states);
}

void Round_Counter::add_round(const unsigned int & p_num, Texture_pack & t)
{
    if(round == p_num)
        round = 1;
    else
        round ++;
    switch (round) {
    case 1:
        sprite.setTexture(t.Player_One);
        break;
    case 2:
        sprite.setTexture(t.Player_Two);
        break;
    case 3:
        sprite.setTexture(t.Player_Three);
        break;
    case 4:
        sprite.setTexture(t.Player_Four);
        break;
    default:
        break;
    }
}
