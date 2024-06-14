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

    //ustawianie ikony okna
    window.setIcon(t.icon.getSize().x, t.icon.getSize().y, t.icon.getPixelsPtr());


    while (window.isOpen())
    {
        //ustawianie pierwszego elementu pętli kontrolnej na true
        controls[0]=true;

        //tworzenie instancjii menu
        menu = std::make_unique <Menu> ();

        //inicjowanie głównego menu;
        menu->initiate_main_menu(t,window);

        while(controls[0]==true)
        {
            //wyswietlanie menu
            menu->gen_menu(window , controls, event, t);

            //sprawdzanie czy przycisk exit został kliknięty
            if(menu->exit_click(window))
            {
                //utworzenie okna zapytania czy na pewno
                if(setings::displayChoiceWindow("",t.font,t.metal,t.icon))
                {
                    window.close();
                    controls[0]=false;
                }
            }

            //sprawdzanie czy przycisk menu (new game został kliknięty
            if(menu->new_game_click(window))
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
                        //wyswietlenie okna z zapytaniem czy gracz zatwierdza decyzje
                        controls[2]=setings::displayChoiceWindow("",t.font,t.metal,t.icon);

                        if(controls[2] == true)
                        {

                            {
                                //tworzenie nicków graczy (tyle graczy ile wynosi initialization_() - liczba graczy wybrana w menu)
                                std::vector <std::string> nicks (menu->p_num_initialization_());

                                //tworzenie okien gdzie poszczególni gracze wpisują nick
                                for(unsigned int i = 1 ; i <= nicks.size() ; i++)
                                    nicks[i-1]=setings::getInputFromWindow(t.font,t.icon,"Player " + std::to_string(i) + " nick");

                                //inicjowanie gry i usuwanie instacji menu bo juz nie jest potrzebna
                                initiate_game(nicks);
                            }

                            while (controls[2]==true)
                            {
                                //petla gry
                                gen();

                                //obsługa zdarzenia położenia tokenu
                                laid_Token::laid(*this);

                                //obsługa zdarzenia gdzie przycisk menu został kliknięty
                                seting->setings_click(*this);

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
    //obsługa zdarzenia zamknięcia okna
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
        {
            window.close();
            //ustawienie petli kontroli na false, by na pewno przerwać każdą pętle
            for(auto it = controls.begin() ; it != controls.end() ; ++it)
            {
                *it = false;
            }
        }
    }
    window.clear(sf::Color(230,255,255));
    //rysowanie wszystkich obiektów z Engine
    window.draw(*this);
}
void Engine::align_tokens()
{
    //iteracja i służy przypisywaniu kolejnych pozycjii tokenom
    for(unsigned int i = 0 ; i <= 5 ; i++)
        {
        vectok->at(i)->reset_rotation();
        vectok->at(i)->align({static_cast<float>(window.getSize().x-750+100*i), 80});
        }
}

//nadpisanie metody draw
void Engine::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    //rysowanie wszystkich elementów
    target.draw(*screen,states);
    target.draw(*board, states);
    target.draw(*round_counter, states);
    for(auto it = score_boards->begin() ; it != score_boards->end() ; ++it)
        target.draw(it->second, states);
    target.draw(*seting.get(),states);
    std::for_each(vectok->begin(),vectok->end(),[&states, &target](const std::unique_ptr <Token> & x){target.draw(*x,states);});


}

void Engine::initiate_game(const std::vector <std::string> & nicks_)
{
    const unsigned int p_num = nicks_.size();
    vectok = std::make_unique <std::vector <std::unique_ptr<Token>>> ();

    //inicjowanie game board z wykorzystaniem wczytanej jako argument liczby graczy
    board = std::make_unique <game_board> (p_num);

    players_map = std::make_unique <std::map <unsigned int, Player>> ();
    //inicjowanie obiektu round counter z pierwszą teksturą (1 runda wiec Player_one)
    round_counter = std::make_unique <Round_Counter> (t.Player_One);

    screen = std::make_unique <sf::RectangleShape> ();
    score_boards = std::make_unique <std::map <unsigned int, Score_board>> ();

    //inicjowanie setings wczytując opowiednie tekstury dla przycisków, przekazując obiekt t
    seting = std::make_unique <setings> (t);

    //inicjowanie dźwieku
    sound = std::make_unique <sf::Sound> ();

    //wygenerowanie planszy
    board->new_board(window);

    //wczytanie tekstury ekranu
    screen->setTexture(&t.main_screen);

    //pozycjonowanie ekranu
    screen->setPosition({0,0});

    //scalowanie ekranu
    screen->setSize({static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y)});

    //generowanie 6 tokenów
    for(unsigned int i = 0; i < 6; i++)
    {
        vectok->emplace_back(std::make_unique<Token>(board->size_()));
    }

    //generowanie odpowiedniej liczby graczy i scoreboardów
    for(unsigned int i = 1 ; i <= p_num ; i++)
    {
        //przypisywanie graczom nicku i numeru
        (*players_map)[i] = Player(nicks_[i-1],i);

        //dla scorebordów graczy 3 i 4 (i > 2)pozycja jest po prawej stronie planszy a dla 1 i 2 po lewej
        if(i > 2)
            (*score_boards)[i] = Score_board(sf::Vector2f(window.getSize().x-250*(i%2+1)-30,250),t.font,t.metal,(*players_map)[i].nick_());
        else
            (*score_boards)[i] = Score_board(sf::Vector2f(250*(i)-180,250),t.font,t.metal,(*players_map)[i].nick_());
    }

    {
        //iteracja i służy temu by kolejne id tokenów gracza (get_Token_id) były przypisywane do vectok
        unsigned int i = 0;
        for(auto & x : *vectok )
        {
            x.get()->token_switch( players_map.get()->at(round_counter->get_round()) .get_Token_id(i).first  ,  players_map.get()->at(round_counter->get_round()) .get_Token_id(i).second );
            i++;
        }
    }

    //wyrównanie i pozycjonowanie tokenów
    align_tokens();

    //usunięcie menu
    menu.reset();
}

void Engine::reset_game()
{
    //wyczyszczenie wszystkich wskaźników
    vectok.reset();
    board.reset();
    round_counter.reset();
    players_map.reset();
    screen.reset();
    score_boards.reset();
    seting.reset();
    game_theme.reset();
}

void Engine::next_round()
{
    //dodanie rundy
    round_counter->add_round(board->players_number(), t);
    {
        int i = 0;
        for(auto & x : *vectok )
        {
            //zmiana tokenów na aktualne
            x.get()->token_switch(players_map->at(round_counter->get_round()).get_Token_id(i).first,players_map->at(round_counter->get_round()).get_Token_id(i).second);
            i++;
        }
    }
}

void Engine::EndGame()
{
    //uzyskiwanie numeru zwyciężcy
    unsigned int winner_num = std::max_element(players_map->begin(),players_map->end(),[](std::pair <unsigned int , Player>  p1 , std::pair <unsigned int , Player> p2){

auto vecp1 = p1.second.pkt();
auto vecp2 = p2.second.pkt();
//sprawdzanie kolejnych elementów posortowanych rosnąco wektorów
for(unsigned int i = 0 ; i <= 5 ; i++)
{
    if(vecp1[i] != vecp2[i])
        return vecp1[i] < vecp2[i];
}

return true;


    })->first;

    //inicjacja okna gratulacjii
    sf::RenderWindow win_window(sf::VideoMode(600, 500), "Congratulations! " + std::to_string(winner_num));

    //funkcja służąca do generowania losowych prostokątów (KONFETII)
    auto random_rec = [&win_window](custom_rectangle &my_rectangle)
    {
        sf::Vector2f position(rand()%win_window.getSize().x, rand()%win_window.getSize().y);
        my_rectangle.setPosition(position);
        my_rectangle.set_speed(rand()%100+100,rand()%100+100,rand()%100+100);
        my_rectangle.set_bounds(0,win_window.getSize().x,0,win_window.getSize().y);
        auto randomkolor = [](sf::Shape &shape){shape.setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));};
        randomkolor(my_rectangle);
    };
    //tworzenie wektora konfetii
    std::vector <custom_rectangle> konfetii(400);
    std::for_each(konfetii.begin(),konfetii.end(),[ &random_rec](custom_rectangle & rec){random_rec(rec);});

    //ustawianie tekstu mówiącego o zwycieżcy
    std::string tex = players_map->at(winner_num).nick_() + " Win";
    sf::Text Text(tex, t.font, 60);
    Text.setFillColor(sf::Color::White);
    Text.setPosition(win_window.getSize().x/2-Text.getGlobalBounds().width/2, win_window.getSize().y/2-Text.getGlobalBounds().height/2.5);

    //zegar slużący do obsługi czasu od ostatniej klatki
    sf::Clock clock;

    //ustawienie ikony okna
    win_window.setIcon(t.icon.getSize().x,t.icon.getSize().y,t.icon.getPixelsPtr());

    // Pobieranie uchwytu okna
    HWND hwnd = win_window.getSystemHandle();

    // Ustawienie okna na zawsze na wierzchu
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    //ustawienie dźwięku gratulacyjnego
    sf::Sound party_theme;
    party_theme.setBuffer(t.party);
    party_theme.setLoop(true);
    party_theme.play();

    while (win_window.isOpen()) {

        //obsługa czasu od ostatniej klatki
        auto elapsed = clock.restart();
        sf::Event event_;
        while (win_window.pollEvent(event_)) {

            if (event_.type == sf::Event::Closed)
                win_window.close();

        }
        win_window.clear(sf::Color::Black);

        //rysowanie każdego kawałka konfetii
        std::for_each(konfetii.begin(),konfetii.end(),[&win_window, &elapsed](custom_rectangle & rec){win_window.draw(rec);rec.animate(elapsed);});

        //rysowanie tekstu
        win_window.draw(Text);
        win_window.display();
    }

    //pokazanie opcjii powrotu do menu
    bool end_ = !setings::displayChoiceWindow("",t.font,t.metal,t.icon,"Menu?");
    controls[0] = end_;
    controls[1] = end_;
    controls[2] = end_;
}
