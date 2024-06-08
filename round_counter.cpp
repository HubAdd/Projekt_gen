#include "round_counter.h"
#include "SFML/Graphics/RenderTarget.hpp"


Round_Counter::Round_Counter():sf::Drawable() {round=1;}



unsigned int Round_Counter::get_round(){return round;}

void Round_Counter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rec , states);
}

void Round_Counter::add_round(const unsigned int & p_num)
{
    if(round == p_num)
        round = 1;
    else
        round ++;
}
