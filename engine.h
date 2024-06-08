#ifndef ENGINE_H
#define ENGINE_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "button.h"
#include "game_board.h"
#include "menu.h"
#include "player.h"
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
    friend void Menu::gen_menu(sf::RenderWindow &Window , std::vector<bool> &controls_ , sf::Event & event);
protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void align_tokens();
    void gen();
    void initiate_game(const unsigned int &p_num);
    void reset_game();
    void next_round();

    std::unique_ptr <game_board> board;
    std::unique_ptr <std::vector <std::unique_ptr<Token>>> vectok ;
    std::unique_ptr <std::map <unsigned int, Player>> players_map;
    std::unique_ptr <Menu> menu;
    std::unique_ptr <Round_Counter> round_counter;

    sf::Event event;
    sf::Clock clock;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1200, 800), "InGenious");
    std::vector <bool> controls = {false,false,false,false,false};
};

#endif // ENGINE_H
