#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "texture_pack.h"

//Menu główne i menu graczy

class Menu
{
public:
    Menu();
    //inicjowanie menu głównego, wczytuje tekstury i okno by dopasować wymiary tekstury ekranu
    void initiate_main_menu(Texture_pack &t, sf::RenderWindow &window);

    //inicjowanie menu graczy, wczytuje tekstury
    void initiate_players_menu(Texture_pack &t);

    //funkcja rysująca menu, bierze za argument okno na ktorym ryzuje, pętle kontroli, jeśli by miało dojść do zamknięcia okna i przerwania jej
    //wczytuje Event by nim zarządzać i tekstury
    void gen_menu(sf::RenderWindow & window, std::vector <bool> & controls_, sf::Event & event, Texture_pack &t);

    //kliknięcie w menu wyboru graczy
    bool click(sf::RenderWindow &window);

    //kliknięcie przycisku cofnięcia z menu graczy do głównego
    bool back_click(sf::RenderWindow &window);

    //klinięcie Exit
    bool exit_click(sf::RenderWindow &window);

    //kliknięcie new_game
    bool new_game_click(sf::RenderWindow &window);

    //pobranie informacjii ile graczy będzie grało
    unsigned int p_num_initialization_();

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
