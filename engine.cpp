#include "engine.h"
#include "laid_token.h"
#include <chrono>
#include <iostream>
#include <thread>
void Engine::main_game_loop()
{
    //ładowanie tekstur
    Texture_pack t;
    if(t.load_textures())
        controls[0]=true;
    else
    {
        std::cerr<<"Error loading textures"<<std::endl;
        window.close();
    }




    while (window.isOpen())
    {
        if(controls[0]==true)
        {
            //tworzenie instancjii menu
            menu = std::make_unique <Menu> ();

            //inicjowanie głównego menu;
            menu->initiate_main_menu(t);

            while(controls[0]==true)
            {
                //wyswietlanie menu
                menu->gen_menu(window , controls, event);

                //sprawdzanie czy przycisk menu (new game został kliknięty
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) and menu->buts[1].mouse_on(window))
                {
                    controls[1]=true;

                    //cool down przed przejsciem do menu wyboru liczby graczy
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    if(controls[1]==true)
                    {
                        //inicjowanie menu wyboru liczby graczy i przy okazji usuwanie porzedniego menu
                        menu->initiate_players_menu(t);
                        while(controls[1]==true)
                        {
                            //wyswietlanie menu
                            menu->gen_menu(window , controls, event);

                            //sprawdzanie czy została wybrana liczba graczy
                            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                //POKOMBINUJ CZY DA SIE ZROBIC TAK ZEBY KLASA ENGINE NIE MUSIALA MIEC DOSTEPU DO BUTS
                                auto pressed_menu_button = std::find_if(menu->buts.begin(),menu->buts.end(),[this](Button & b){return b.mouse_on(window);});
                                if(pressed_menu_button != menu->buts.end())
                                {
                                    controls[2]=true;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                    if(controls[2] == true)
                                    {
                                        //inicjowanie gry i usuwanie instacji menu bo juz nie jest potrzebna
                                        //ZMIEN METODE GETNUM
                                        initiate_game(pressed_menu_button -> get_num());
                                        while (controls[2]==true)
                                        {
                                            //petla gry
                                            gen();
                                            laid_Token::laid(*this);
                                            window.display();
                                        }
                                        // 3 element petli kotroli zostal ustawiony na false,
                                        //zatem dokonany zostanie powrót do menu,
                                        //więc instancje potrzebne do działania rozgrywki są juz nie potrzebne
                                        reset_game();
                                    }
                                }
                            }
                            window.display();
                        }
                    }
                }
                window.display();
            }
        }
    }
}
void Engine::gen()
{
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
        {
            window.close();
            for(auto it = controls.begin() ; it != controls.end() ; ++it)
            {
                *it = false;
            }
        }
    }
    window.clear(sf::Color(230,255,255));
    window.draw(*this);
}
void Engine::align_tokens()
{

    for(int i = 0 ; i <= 2 ; i++)
        {
        vectok.get()->at(0+2*i)->reset_rotation();
        vectok.get()->at(1+2*i)->reset_rotation();
        vectok.get()->at(0+2*i)->align({static_cast<float>(window.getSize().x-100), static_cast<float>(window.getSize().y-150-150*i)});
        vectok.get()->at(1+2*i)->align({static_cast<float>(window.getSize().x-200), static_cast<float>(window.getSize().y-150-150*i)});
        }
}

void Engine::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(*board, states);
    for(auto & x : *vectok)
    {
        if(x != NULL)
            target.draw(*x,states);
    }

}

void Engine::initiate_game(const unsigned int & p_num)
{
    vectok = std::make_unique <std::vector <std::unique_ptr<Token>>> ();
    board = std::make_unique <game_board> (p_num);
    players_map = std::make_unique <std::map <unsigned int, Player>> ();
    round_counter = std::make_unique <Round_Counter> ();
    board->new_board(window);

    for(int i = 0; i < 6; i++)
    {
        vectok->emplace_back(std::make_unique<Token>(board->size_()));
    }
    for(unsigned int i = 1 ; i <= p_num ; i++)
    {
        (*players_map)[i] = Player("n",i);
    }

    {
        int i = 0;
        for(auto & x : *vectok )
        {
            x.get()->token_switch(players_map.get()->at(round_counter->get_round()).get_Token_id(i).first,players_map.get()->at(round_counter->get_round()).get_Token_id(i).second);
            i++;
        }
    }

    align_tokens();
    menu.get_deleter();
}

void Engine::reset_game()
{
    vectok.get_deleter();
    board.get_deleter();
    round_counter.get_deleter();
    players_map.get_deleter();
}

void Engine::next_round()
{
    round_counter->add_round(board->players_number());
    {
        int i = 0;
        for(auto & x : *vectok )
        {
            x.get()->token_switch(players_map->at(round_counter->get_round()).get_Token_id(i).first,players_map->at(round_counter->get_round()).get_Token_id(i).second);
            i++;
        }
    }
}
