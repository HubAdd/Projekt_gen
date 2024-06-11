#include "engine.h"
#include "custom_rectangle.h"
#include "laid_token.h"
#include "setings.h"
#include <chrono>
#include <iostream>
#include <thread>
void Engine::main_game_loop()
{
    //ładowanie tekstur

    if(!t.load_textures())
    {
        std::cerr<<"Error loading textures"<<std::endl;
        window.close();
    }
    window.setIcon(t.icon.getSize().x, t.icon.getSize().y, t.icon.getPixelsPtr());


    while (window.isOpen())
    {
        controls[0]=true;

        //tworzenie instancjii menu
        menu = std::make_unique <Menu> ();

        //inicjowanie głównego menu;
        menu->initiate_main_menu(t,window);

        while(controls[0]==true)
        {
            //wyswietlanie menu
            menu->gen_menu(window , controls, event, t);

            //sprawdzanie czy przycisk menu (new game został kliknięty
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) and menu->buts[1].mouse_on(window))
            {
                controls[1]=true;

                //cool down przed przejsciem do menu wyboru liczby graczy
                std::this_thread::sleep_for(std::chrono::milliseconds(500));

                //inicjowanie menu wyboru liczby graczy i przy okazji usuwanie porzedniego menu
                menu->initiate_players_menu(t);
                while(controls[1]==true)
                {
                    //wyswietlanie menu
                    menu->gen_menu(window , controls, event, t);

                    //sprawdzanie czy nastąpiło wycofanie do Menu głównego
                    if(menu->back_click(window))
                    {
                        controls[1]=false;
                        controls[0]=false;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }


                    //sprawdzanie czy została wybrana liczba graczy
                    if(menu->click(window))
                    {
                        controls[2]=setings::displayChoiceWindow("",t.font,t.metal,t.icon);

                        if(controls[2] == true)
                        {
                            //inicjowanie gry i usuwanie instacji menu bo juz nie jest potrzebna
                            initiate_game(menu->p_num_initialization_());
                            while (controls[2]==true)
                            {
                                //petla gry
                                gen();
                                laid_Token::laid(*this);
                                if(seting->setings_click(window,t))
                                {
                                    controls[2]=false;
                                    controls[1]=false;
                                    controls[0]=false;
                                }

                                window.display();
                            }
                            // 3 element petli kotroli zostal ustawiony na false,
                            //zatem dokonany zostanie powrót do menu,
                            //więc instancje potrzebne do działania rozgrywki są juz nie potrzebne
                            reset_game();
                        }
                    }
                    window.display();
                }
            }
            window.display();
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

    for(int i = 0 ; i <= 5 ; i++)
        {
        vectok.get()->at(i)->reset_rotation();
        vectok.get()->at(i)->align({static_cast<float>(window.getSize().x-750+100*i), 80});
        }
}

void Engine::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(*screen,states);
    target.draw(*board, states);
    std::for_each(vectok->begin(),vectok->end(),[&states, &target](const std::unique_ptr <Token> & x)
    {
        if(x != NULL)
            target.draw(*x,states);
    });
    target.draw(*round_counter, states);
    for(auto it = score_boards->begin() ; it != score_boards->end() ; ++it)
        target.draw(it->second, states);
    target.draw(*seting.get(),states);


}

void Engine::initiate_game(const unsigned int & p_num)
{
    vectok = std::make_unique <std::vector <std::unique_ptr<Token>>> ();
    board = std::make_unique <game_board> (p_num);
    players_map = std::make_unique <std::map <unsigned int, Player>> ();
    round_counter = std::make_unique <Round_Counter> (t.Player_One);
    screen = std::make_unique <sf::RectangleShape> ();
    score_boards = std::make_unique <std::map <unsigned int, Score_board>> ();
    seting = std::make_unique <setings> (t);


    board->new_board(window);
    screen->setTexture(&t.main_screen);
    screen->setPosition({0,0});

    screen->setSize({static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y)});

    for(int i = 0; i < 6; i++)
    {
        vectok->emplace_back(std::make_unique<Token>(board->size_()));
    }
    for(unsigned int i = 1 ; i <= p_num ; i++)
    {
        std::string nick = setings::getInputFromWindow(t.font,t.icon,"Player " + std::to_string(i) + " nick");
        (*players_map)[i] = Player(nick,i);

        if(i > 2)
            (*score_boards)[i] = Score_board(sf::Vector2f(window.getSize().x-250*(i%2+1)-30,250),t.font,t.metal,(*players_map)[i].nick_());
        else
            (*score_boards)[i] = Score_board(sf::Vector2f(250*(i)-180,250),t.font,t.metal,(*players_map)[i].nick_());
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
    menu.reset();
}

void Engine::reset_game()
{
    vectok.reset();
    board.reset();
    round_counter.reset();
    players_map.reset();
    screen.reset();
    score_boards.reset();
    seting.reset();

}

void Engine::next_round()
{
    round_counter->add_round(board->players_number(), t);
    {
        int i = 0;
        for(auto & x : *vectok )
        {
            x.get()->token_switch(players_map->at(round_counter->get_round()).get_Token_id(i).first,players_map->at(round_counter->get_round()).get_Token_id(i).second);
            i++;
        }
    }
}

void Engine::EndGame()
{
    unsigned int winner_num = std::max_element(players_map->begin(),players_map->end(),[](std::pair <unsigned int , Player>  p1 , std::pair <unsigned int , Player> p2){

auto vecp1 = p1.second.pkt();
auto vecp2 = p2.second.pkt();
for(unsigned int i = 0 ; i <= 5 ; i++)
{
    if(vecp1[i] != vecp2[i])
        return vecp1[i] < vecp2[i];
}

return true;


    })->first;

    sf::RenderWindow win_window(sf::VideoMode(600, 500), "Congratulations! " + std::to_string(winner_num));
    auto random_rec = [&win_window](custom_rectangle &my_rectangle)
    {
        sf::Vector2f position(rand()%win_window.getSize().x, rand()%win_window.getSize().y);
        my_rectangle.setPosition(position);
        my_rectangle.set_speed(rand()%100+100,rand()%100+100,rand()%100+100);
        my_rectangle.set_bounds(0,win_window.getSize().x,0,win_window.getSize().y);
        auto randomkolor = [](sf::Shape &shape){shape.setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));};
        randomkolor(my_rectangle);
        //my_rectangle.setFillColor(sf::Color(250,250,250));
    };

    std::vector <custom_rectangle> konfetii(400);
    std::for_each(konfetii.begin(),konfetii.end(),[ &random_rec](custom_rectangle & rec){random_rec(rec);});
    std::string tex = players_map->at(winner_num).nick_() + " Win";
    sf::Text Text(tex, t.font, 60);
    Text.setFillColor(sf::Color::White);
    Text.setPosition(win_window.getSize().x/2-Text.getGlobalBounds().width/2, win_window.getSize().y/2-Text.getGlobalBounds().height/2.5);

    sf::Clock clock;

    win_window.setIcon(t.icon.getSize().x,t.icon.getSize().y,t.icon.getPixelsPtr());

    // Pobieranie uchwytu okna
    HWND hwnd = win_window.getSystemHandle();

    // Ustawienie okna na zawsze na wierzchu
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    sf::Sound party_theme;
    party_theme.setBuffer(t.party);
    party_theme.setLoop(true);
    party_theme.play();

    while (win_window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop

        auto elapsed = clock.restart();
        sf::Event event_;
        while (win_window.pollEvent(event_)) {
            // "close requested" event: we close the window
            if (event_.type == sf::Event::Closed)
                win_window.close();

        }



        // clear the window with black color
        win_window.clear(sf::Color::Black);
        std::for_each(konfetii.begin(),konfetii.end(),[&win_window, &elapsed](custom_rectangle & rec){win_window.draw(rec);rec.animate(elapsed);});
        win_window.draw(Text);
        win_window.display();
    }
    bool end_ = !setings::displayChoiceWindow("",t.font,t.metal,t.icon,"Menu?");
    controls[0] = end_;
    controls[1] = end_;
    controls[2] = end_;
}
