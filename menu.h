#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "texture_pack.h"

class Menu
{
public:
    Menu();
    void initiate_main_menu(Texture_pack &t);
    void initiate_players_menu(Texture_pack &t);
    void gen_menu(sf::RenderWindow & window, std::vector <bool> & controls_, sf::Event & event);
    friend class Engine;
protected:
    std::vector <Button> buts;
};

#endif // MENU_H
