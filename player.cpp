#include "player.h"
Player::Player(){}
Player::Player(const std::string & nick_, const unsigned int & num) : nick(nick_),Player_number(num)
{
    for(int i = 0 ; i < 6 ; i++)
        Tokens_id.emplace_back(rand()%6+1,rand()%6+1);
}

std::pair <unsigned int, unsigned int> Player::get_Token_id(const unsigned int &num)
{
    return Tokens_id[num];
}

void Player::change (const std::vector <std::pair<unsigned int, unsigned int>> & vec)
{
    Tokens_id = vec;
}
void Player::add_point (const unsigned int & t)
{
    Points[t]=Points[t]+1;
}
