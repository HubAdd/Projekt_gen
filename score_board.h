#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H
#include "SFML/Graphics/Drawable.hpp"
#include "sextangle.h"
class Score_board : public sf::Drawable
{
public:
    Score_board();
    Score_board(const sf::Vector2f &pos, sf::Font & font, sf::Texture & metal_, const std::string & nick);
    void ilustrate_possible_points(std::map < unsigned int , unsigned int > & possible_Points, std::map < unsigned int , unsigned int > Player_Points);
    void erase_ilustration();
    void move_(const unsigned int & num, const float & down);
    bool stop_animation(const unsigned int & num , const unsigned int & destination);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    std::vector <std::unique_ptr<sextangle>> vec2;
    std::vector <std::unique_ptr<sextangle>> Points_counters;
    sf::RectangleShape background;
    std::vector <sf::Text> num_list;
    sf::Text caption;
};

#endif // SCORE_BOARD_H
