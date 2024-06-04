#include "game_board.h"
#include <cmath>


void game_board::reset()
{
    for(auto &x : vec1)
    {
        x->setFillColor(sf::Color::White);
    }
    reset_lines();
}

void game_board::new_board(sf::RenderWindow &window)
{
    size=(window.getSize().y/32);
    vec1.clear();
    sf::Vector2f vec60_30 = {static_cast<float>(sqrt(3)/2),static_cast<float>(0.5)};
    const int l=3+players_number_;
    sf::Vector2f Null_position(window.getSize().x/2,window.getSize().y/2);
    Null_position-=(static_cast<const float>(l*2.1*sqrt(3)*size/2)*vec60_30);
    vec60_30.y*=-1;
    auto generate_sextangle = [&Null_position,&vec60_30, &l, this](sf::Vector2i pos)
    {
        sf::Vector2f pos_vector;
        sextangle s(size);
        pos_vector=(Null_position+(static_cast<const float>(pos.x*2.05)*s.h_()*sf::Vector2f(0,1))+(static_cast<const float>(pos.y*2.05)*s.h_()*vec60_30));
        if(pos.y>l)
            pos_vector.y+=(pos.y-l)*2.05*s.h_();
        s.setPosition(pos_vector);
        vec1.emplace_back(std::make_unique<sextangle>(s));

    };
    for(int n=0;n<=l;n++)
    {
        for(int i=0;i<=l+n;i++)
        {
            generate_sextangle({i,n});
        }
    }
    for(int n=l+1;n<=2*l;n++)
    {
        for(int i=0;i<=2*l-1-n%(l+1);i++)
        {
            generate_sextangle({i,n});
        }
    }
    for(auto & x : vec1)
    {
        x->setOutlineColor(sf::Color::Cyan);
        x->setOutlineThickness(2);
    }
}


void game_board::reset_lines()
{
    for(auto &x : vec1)
    {
        x->setOutlineColor(sf::Color::Cyan);
        x->setOutlineThickness(2);
    }
}
