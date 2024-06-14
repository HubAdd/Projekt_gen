#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H
#include "SFML/Graphics/Drawable.hpp"
#include "sextangle.h"

//klasa ilustrująca ile pkt mają gracze i animuje ile moga zdobyć przy danym ruchu

class Score_board : public sf::Drawable
{
public:
    Score_board();
    //przyjmuje argument pozycjii i nick gracza którego jest
    Score_board(const sf::Vector2f &pos, sf::Font & font, sf::Texture & metal_, const std::string & nick);

    //animuje ile moga zdobyć przy danym ruchu
    void ilustrate_possible_points(std::map < unsigned int , unsigned int > & possible_Points, std::map < unsigned int , unsigned int > Player_Points);

    //usuwa ilustracje
    void erase_ilustration();

    //przesuwa o argument down w dół wskaźnik pkt o danym indeksie num
    void move_(const unsigned int & num, const float & down);

    //zwraca true, do momentu wskaźnik o danym num dotrze do celu (cel to miejsce gdzie wskaże aktualną ilość pkt
    bool stop_animation(const unsigned int & num , const unsigned int & destination);

    //nadpisana metoda draw
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    //atrybuty czysto graficzne
    //wektor sześciokątów, z ktorych składa się scoreboard
    std::vector <std::unique_ptr<sextangle>> vec2;

    //wskaźniki ilości pkt
    std::vector <std::unique_ptr<sextangle>> Points_counters;

    //tło scorebordu
    sf::RectangleShape background;

    //wektor wyświetlanych cyfr
    std::vector <sf::Text> num_list;

    //text który bierze nick gracza
    sf::Text caption;
};

#endif // SCORE_BOARD_H
