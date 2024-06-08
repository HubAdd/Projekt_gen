#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
class Player
{
public:
    Player();
    Player(const std::string & nick_, const unsigned int & num);
    std::pair <unsigned int, unsigned int> get_Token_id(const unsigned int & num);
    void change (const std::vector <std::pair<unsigned int, unsigned int>> & vec);
    void add_point (const unsigned int & t);

private:
    std::string nick;
    unsigned int Player_number;
    std::vector <std::pair<unsigned int, unsigned int>> Tokens_id;
    std::vector <unsigned int> Points;
};

#endif // PLAYER_H
