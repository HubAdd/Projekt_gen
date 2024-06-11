#include "game_board.h"
#include "additionalshapedecorator.h"
#include <cmath>

game_board::game_board(){}


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
    reset_lines();


    std::vector <unsigned int> vec;

    auto change = [this](const unsigned int a,const unsigned int & type)
    {
        auto s = std::move(vec1[a]);
        vec1[a] = std::make_unique <AdditionalShapeDecorator> (std::move(s),type);
        static_cast <AdditionalShapeDecorator*> (vec1[a].get())->setposition(vec1[a]->getPosition());
    };
    if(players_number_ == 2)
        vec = {40,5,90,50,85,0};
    if(players_number_ == 3)
        vec = {58,13,118,68,113,8};
    if(players_number_ == 4)
        vec = {79,24,149,89,144,19};

    for(unsigned int i = 1 ; i <= 6 ; i++)
        change(vec[i-1],i);

}
bool game_board::no_space()
{
    return !std::any_of(vec1.begin(),vec1.end(),[this](const std::unique_ptr <sextangle> & s)
    {
        if(s->getFillColor()==sf::Color::White)
        {
            return std::any_of(vec1.begin(),vec1.end(),[&s](const std::unique_ptr <sextangle> & s1)
            {
                return s1->getFillColor()==sf::Color::White and s1 != s and sqrt(pow(s->getPosition().x-s1->getPosition().x,2)+pow(s->getPosition().y-s1->getPosition().y,2)) < 2.5 * s->h_();
            });
        }
        else
            return false;
    ;});
}

void game_board::reset_lines()
{
    std::for_each(vec1.begin(),vec1.end(),[](const std::unique_ptr <sextangle> & s){s->setOutlineColor(sf::Color::Cyan);s->setOutlineThickness(2);;});
}

void game_board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    std::for_each(vec1.begin(),vec1.end(),[&states, &target](const std::unique_ptr <sextangle> & s){target.draw(*s , states);});
}
