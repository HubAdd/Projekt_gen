#include "engine.h"
#include "laid_token.h"
void Engine::main_game_loop(sf::RenderWindow & window)
{
    board.new_board(window);
    vectok.emplace_back(std::make_unique<Token>(board.size_()));
    vectok.emplace_back(std::make_unique<Token>(board.size_()));

    vectok.emplace_back(std::make_unique<Token>(board.size_()));
    vectok.emplace_back(std::make_unique<Token>(board.size_()));

    vectok.emplace_back(std::make_unique<Token>(board.size_()));
    vectok.emplace_back(std::make_unique<Token>(board.size_()));

    for(auto x = vectok.begin() ; x != vectok.end() ; ++x)
        x->get()->token_switch(rand()%6 + 1,rand()%6 + 1);

    align_tokens(window);
    while (window.isOpen()) {
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(230,255,255));
        window.draw(*this);
        window.display();
        laid_Token::laid(*this,window);
    }

}
void Engine::gen(std::vector <bool> & loop_controls, sf::RenderWindow &window)
{
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
        {
            window.close();
            for(auto it = loop_controls.begin() ; it != loop_controls.end() ; ++it)
            {
                *it=false;
            }
        }
    }
    window.clear(sf::Color(230,255,255));
    window.draw(*this);
}
void Engine::align_tokens(sf::RenderWindow & window)
{

    for(int i = 0 ; i <= 2 ; i++)
        {
        vectok[0+2*i]->reset_rotation();
        vectok[1+2*i]->reset_rotation();
        vectok[0+2*i]->align({static_cast<float>(window.getSize().x-100), static_cast<float>(window.getSize().y-150-150*i)});
        vectok[1+2*i]->align({static_cast<float>(window.getSize().x-200), static_cast<float>(window.getSize().y-150-150*i)});
        }
}
