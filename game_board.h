#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "sextangle.h"
class game_board : public sf::Drawable
{
public:
    game_board();
    game_board(const unsigned int &num):
        players_number_(num){}
    void new_board(sf::RenderWindow &window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void reset_lines();
    bool no_space();
    unsigned int players_number(){return players_number_;}
    float size_(){return size;}
    friend class laid_Token;
    friend class Engine;

private:
    unsigned int players_number_;
    std::vector <std::unique_ptr<sextangle>> vec1;
    float size;


};

#endif // GAME_BOARD_H
