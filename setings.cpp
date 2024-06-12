#include "setings.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "engine.h"
#include <chrono>
#include <thread>


setings::setings(Texture_pack & t)
{
    Back_to_menu_button = std::make_unique <Button> (sf::Vector2f(0,-20),t.Three_P,t.font,"Menu",0.1);
    Back_to_menu_button.get()->text.setFillColor(sf::Color::White);
    Back_to_menu_button.get()->text.move(0,-10);

    Info_button = std::make_unique <Button> (sf::Vector2f(Back_to_menu_button.get()->react.getGlobalBounds().width,-20),t.Three_P,t.font,"Info",0.1);
    Info_button.get()->text.setFillColor(sf::Color::White);
    Info_button.get()->text.move(0,-10);

    Reset_button = std::make_unique <Button> (sf::Vector2f(Back_to_menu_button.get()->react.getGlobalBounds().width+Info_button.get()->react.getGlobalBounds().width,-20),t.Three_P,t.font,"Reset",0.1);
    Reset_button.get()->text.setFillColor(sf::Color::White);
    Reset_button.get()->text.move(0,-10);

    Music_button = std::make_unique <Button> (sf::Vector2f(Reset_button->react.getGlobalBounds().left+Reset_button->react.getGlobalBounds().width,-20),t.Three_P,t.font,"Music",0.1);
    Music_button->text.setFillColor(sf::Color::White);
    Music_button->text.move(0,-10);
}

void setings::setings_click(Engine & E)
{

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(Back_to_menu_button->mouse_on(E.window))
            if(displayChoiceWindow("Progress will be lost",E.t.font,E.t.metal,E.t.icon))
            {
                //powrócenie do początku pętli kontroli (Menu)
                E.controls[2]=false;
                E.controls[1]=false;
                //ten element też na false, by wywołać zainicjowanie menu
                E.controls[0]=false;
            }
        if(Music_button->mouse_on(E.window))
        {
            if(E.game_theme == NULL)
                E.game_theme = std::make_unique <sf::Sound>();
            setSoundFromWindow(E.t,*E.game_theme.get());

        }




        if(Info_button->mouse_on(E.window))
        {
            // Tworzenie okna
            sf::RenderWindow window(sf::VideoMode(1440, 810), "Game Info", sf::Style::Titlebar | sf::Style::Close);

            window.setIcon(E.t.icon.getSize().x,E.t.icon.getSize().y,E.t.icon.getPixelsPtr());

            // Pobieranie uchwytu okna
            HWND hwnd = window.getSystemHandle();

            // Ustawienie okna na zawsze na wierzchu
            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);



            sf::RectangleShape rec;
            rec.setTexture(&E.t.gold);
            rec.setSize({1440,810});
            rec.setPosition({0,0});

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }


                }

                window.clear();
                window.draw(rec);
                window.display();
            }
        }
        if(Reset_button->mouse_on(E.window))
        {
            if(displayChoiceWindow("Progress will be lost",E.t.font,E.t.metal,E.t.icon))
            {
                std::vector <std::string> nicks;
                for(auto it = E.players_map->begin() ; it != E.players_map->end() ; it++)
                {
                    nicks.emplace_back(it->second.nick_());
                }
                E.reset_game();
                E.initiate_game(nicks);
            }
        }
    }
}

void setings::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*Back_to_menu_button.get() , states);
    target.draw(*Info_button.get() , states);
    target.draw(*Reset_button.get() , states);
    target.draw(*Music_button.get(),states);
}

bool setings::displayChoiceWindow(const std::string& tex, sf::Font & font , sf::Texture & t, sf::Image &I, const std::string& title) {

    // Tworzenie okna
    sf::RenderWindow window(sf::VideoMode(300, 150), title, sf::Style::Titlebar | sf::Style::Close);

    window.setIcon(I.getSize().x,I.getSize().y,I.getPixelsPtr());

    // Pobieranie uchwytu okna
    HWND hwnd = window.getSystemHandle();

    // Ustawienie okna na zawsze na wierzchu
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    // Tworzenie tekstów dla opcji

    sf::RectangleShape rec;
    rec.setTexture(&t);
    rec.setSize({300,150});
    rec.setPosition({0,0});

    sf::Text Text(tex, font, 16);
    Text.setFillColor(sf::Color::Black);
    Text.setPosition(5, 5);

    sf::Text yesText("Yes", font, 20);
    yesText.setFillColor(sf::Color::Black);
    yesText.setPosition(75, 50);

    sf::Text noText("No", font, 20);
    noText.setFillColor(sf::Color::Black);
    noText.setPosition(175, 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (yesText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

                        window.close();
                        return true;
                    }
                    if (noText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

                        window.close();
                        return false;
                    }
                }
            }
        }

        window.clear();
        window.draw(rec);
        window.draw(yesText);
        window.draw(noText);
        window.draw(Text);
        window.display();
    }

    return false; // Default value if window is closed without selection
}

std::string setings::getInputFromWindow(sf::Font & font, sf::Image &I, const std::string& title) {
    sf::RenderWindow window(sf::VideoMode(400, 200), title);

    window.setIcon(I.getSize().x,I.getSize().y,I.getPixelsPtr());

    // Pobieranie uchwytu okna
    HWND hwnd = window.getSystemHandle();

    // Ustawienie okna na zawsze na wierzchu
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    sf::Text text("", font, 24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 80);

    std::string input;
    bool enterPressed = false;

    while (window.isOpen() && !enterPressed) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b') { // Handle backspace
                        if (!input.empty()) {
                            input.pop_back();
                        }
                    } else if (event.text.unicode == '\r') { // Handle enter
                        enterPressed = true;
                    } else if (input.size() < 12) {
                        input += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }

        text.setString(input + "_");
        window.clear();
        window.draw(text);
        window.display();
    }

    window.close();
    return input;
}
void setings::setSoundFromWindow(Texture_pack &t , sf::Sound & s)
{
    //liczba przycisków
    const unsigned int but_num = 6;
    std::vector <Button> buts;
    buts.emplace_back( Button(sf::Vector2f(60,30),t.Three_P,t.font,"Sound 1",0.1) );
    for(unsigned int i = 1 ; i < but_num ; i++)
    {
        buts.emplace_back( Button(sf::Vector2f(60,i*buts[0].react.getGlobalBounds().height),t.Three_P,t.font,"Sound 1",0.1) );
    }
    std::for_each(buts.begin(),buts.end(),[](Button & b){b.text.setFillColor(sf::Color::White);b.text.move(0,-25);});

    buts[0].text.setString("ON");
    buts[1].text.setString("OFF");
    buts[2].text.setString("Party");
    buts[3].text.setString("Guitar");
    buts[4].text.setString("Street");
    buts[5].text.setString("RIO");


    sf::RenderWindow window(sf::VideoMode(buts[0].react.getGlobalBounds().width+120, buts.back().react.getGlobalBounds().top+buts.back().react.getGlobalBounds().height+60), "Choose Music", sf::Style::Titlebar | sf::Style::Close);

    window.setIcon(t.icon.getSize().x,t.icon.getSize().y,t.icon.getPixelsPtr());

    // Pobieranie uchwytu okna
    HWND hwnd = window.getSystemHandle();

    // Ustawienie okna na zawsze na wierzchu
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Cyan);
        std::for_each(buts.begin(),buts.end(),[&window](const Button & b){window.draw(b);});
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            auto b = std::find_if(buts.begin(),buts.end(),[&window](Button & bb){return bb.mouse_on(window);});
            if(b != buts.end())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                const unsigned int choose = std::distance(buts.begin(),b);
                if(!s.getLoop())
                    s.setLoop(true);
                switch (choose) {
                case 0:
                    s.play();
                    break;
                case 1:
                    s.pause();
                    break;
                case 2:
                    s.setBuffer(t.party);
                    s.play();
                    break;
                case 3:
                    s.setBuffer(t.guitar);
                    s.play();
                    break;
                case 4:
                    s.setBuffer(t.street);
                    s.play();
                    break;
                case 5:
                    s.setBuffer(t.RIO);
                    s.play();
                    break;
                default:
                    break;
                }

            }

        }
        window.display();
    }
}
