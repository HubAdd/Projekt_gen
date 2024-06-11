#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "texture_pack.h"

class Menu
{
public:
    Menu();
    void initiate_main_menu(Texture_pack &t, sf::RenderWindow &window);
    void initiate_players_menu(Texture_pack &t);
    void gen_menu(sf::RenderWindow & window, std::vector <bool> & controls_, sf::Event & event, Texture_pack &t);
    bool click(sf::RenderWindow &window);
    bool back_click(sf::RenderWindow &window);
    unsigned int p_num_initialization_();
    friend class Engine;
protected:
    std::unique_ptr <unsigned int> p_num_initialization;
    std::vector <Button> buts; //wektor przycisków
    sf::RectangleShape logo_; //logo nie odwrócone
    sf::RectangleShape screen; //textura na ekran
    unsigned int logo_it=4; //iterator służący do zmieniania tekstury loga
    unsigned int logo_it_it=0; //iterator mierzy ticki (30 ticków to jedno zwiększenie logo_it)
    std::unique_ptr <sf::Text> Back;
    sf::Sound theme;
};

#endif // MENU_H
