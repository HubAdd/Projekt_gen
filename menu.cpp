#include "menu.h"
#include "SFML/Window/Event.hpp"
#include "texture_pack.h"
Menu::Menu() {}

void Menu::initiate_main_menu(Texture_pack & t)
{
    buts.clear();

    buts.emplace_back(Button({900,400},t.Two_P));
    buts.emplace_back(Button({100,400},t.Three_P));
}


void Menu::initiate_players_menu(Texture_pack & t)
{
    buts.clear();

    buts.emplace_back(Button({550,400},t.Two_P));
    buts.emplace_back(Button({550,500},t.Three_P));
    buts.emplace_back(Button({550,600},t.Four_P));

}


void Menu::gen_menu(sf::RenderWindow &window , std::vector<bool> &controls_ , sf::Event & event )
{
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
        {
            window.close();
            for(auto it = controls_.begin() ; it != controls_.end() ; ++it)
            {
                *it = false;
            }
        }
    }
    window.clear(sf::Color(230,255,255));
    for(auto & x : buts)
    {
        x.draw(window);
    }
}
