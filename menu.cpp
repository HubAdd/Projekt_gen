#include "menu.h"
#include "SFML/Window/Event.hpp"
#include "texture_pack.h"
Menu::Menu() {}

void Menu::initiate_main_menu(Texture_pack & t, sf::RenderWindow & window)
{
    theme.setBuffer(t.void_);
    theme.setLoop(true);
    theme.play();
    theme.setVolume(20);
    buts.clear();
    Back.reset();

    logo_.setPosition(600,200);
    logo_.setSize({720,405});

    screen.setTexture(&t.Four_P);
    screen.setPosition(0,0);
    screen.setSize({static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y)});

    buts.emplace_back(Button({195,600},t.Four_P,t.font1,"Exit",0.2));
    buts.emplace_back(Button({1345,600},t.Four_P,t.font1,"New Game",0.2));

    std::for_each(buts.begin(),buts.end(),[](Button & b){b.text.move(0,12);});
}


void Menu::initiate_players_menu(Texture_pack & t)
{
    buts.clear();

    buts.emplace_back(Button({195,600},t.Four_P,t.font1,"Two Players",0.2));
    buts.emplace_back(Button({768,600},t.Four_P,t.font1,"Three Players",0.2)); //650 1000 1250
    buts.emplace_back(Button({1345,600},t.Four_P,t.font1,"Four Players",0.2));

    Back = std::make_unique <sf::Text> ("Back",t.font,44);
    Back->setFillColor(sf::Color::White);
    Back->setPosition({0,0});

    std::for_each(buts.begin(),buts.end(),[](Button & b){b.text.move(0,12);});



}


void Menu::gen_menu(sf::RenderWindow &window , std::vector<bool> &controls_ , sf::Event & event ,  Texture_pack & t)
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
    window.clear(sf::Color::Black);
    window.draw(screen);
    if(Back != NULL)
        window.draw(*Back.get());
    std::for_each(buts.begin(),buts.end(),[&window](const Button & b){window.draw(b);});
    window.draw(logo_);
    logo_it_it++;
    if(logo_it_it==30)
    {
        logo_it_it=0;
        logo_.setTexture(&t.logo_animation[logo_it]);
        logo_it++;
        if(logo_it == 88)
            logo_it=0;
    }

}

bool Menu::click(sf::RenderWindow & window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(buts[0].mouse_on(window))
            p_num_initialization = std::make_unique <unsigned int> (2);
        else if(buts[1].mouse_on(window))
            p_num_initialization = std::make_unique <unsigned int> (3);
        else if(buts[2].mouse_on(window))
            p_num_initialization = std::make_unique <unsigned int> (4);
        else return false;
        return true;
    }
    else
        return false;
}

bool Menu::back_click(sf::RenderWindow &window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) and Back->getGlobalBounds().contains({static_cast<float>(sf::Mouse::getPosition(window).x),static_cast<float>(sf::Mouse::getPosition(window).y)}))
        return true;
    else
        return false;

}

unsigned int Menu::p_num_initialization_()
{
    return *std::move(p_num_initialization);
}
