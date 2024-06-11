#include "player.h"
#include <algorithm>
#include <iostream>
Player::Player(){}
Player::Player(const std::string & nick_, const unsigned int & num) : nick(nick_),Player_number(num)
{
    for(int i = 0 ; i < 6 ; i++)
    {
        Tokens_id.emplace_back(rand()%6+1,rand()%6+1);
        Is_Genious[i+1]=false;
    }

}

std::pair <unsigned int, unsigned int> Player::get_Token_id(const unsigned int & num)
{
    return Tokens_id[num];
}

void Player::change (const std::vector <std::pair<unsigned int, unsigned int>> & vec)
{
    Tokens_id = vec;
}
void Player::add_point (std::map < unsigned int , unsigned int > & Points_)
{
    for( int i = 1 ; i <= 6 ; i++)
    {
        Points[i]=Points[i]+Points_[i];
        if(Points[i] > 18)
            Points[i]=18;
    }

}

void Player::show()
{
    std::cout << "Pkt Gracza nr " << Player_number << std::endl ;
    for( int i = 1 ; i <= 6 ; i++)
    {
        std::cout << i << " : ";
        std::cout << Points[i] << std::endl;

    }
    std::cout << std::endl ;

}


std::string Player::nick_(){return nick;};

std::vector <unsigned int> Player::pkt()
{
    std::vector <unsigned int> pkt_;
    for(auto it = Points.begin() ; it != Points.end() ; ++it)
    {
        pkt_.emplace_back(it->second);
    }
    std::sort(pkt_.begin(),pkt_.end());
    return pkt_;
}
