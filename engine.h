#ifndef ENGINE_H
#define ENGINE_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "button.h"
#include "game_board.h"
#include "menu.h"
#include "player.h"
#include "score_board.h"
#include "setings.h"
#include "token.h"
#include <memory>
#include <round_counter.h>


class Engine : public sf::Drawable
{
public:
    Engine(){}
    void main_game_loop();
    friend class laid_Token;
    friend class Round_Counter;
    friend void Menu::gen_menu(sf::RenderWindow &Window , std::vector<bool> &controls_ , sf::Event & event, Texture_pack &t);
protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void align_tokens();
    void gen();
    void initiate_game(const unsigned int &p_num);
    void reset_game();
    void next_round();
    void EndGame();

    std::unique_ptr <game_board> board;
    std::unique_ptr <std::vector <std::unique_ptr<Token>>> vectok ;
    std::unique_ptr <std::map <unsigned int, Player>> players_map;
    std::unique_ptr <Menu> menu;
    std::unique_ptr <Round_Counter> round_counter;
    std::unique_ptr <sf::RectangleShape> screen;
    std::unique_ptr <std::map <unsigned int, Score_board>> score_boards;
    std::unique_ptr <sf::Text> Ingenious;
    std::unique_ptr <setings> seting;

    sf::Sound sound;
    sf::Event event;
    Texture_pack t;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920, 1080), "InGenious" , sf::Style::Default);

    std::vector <bool> controls = {false,false,false,false,false};
};

#endif // ENGINE_H
