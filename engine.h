#ifndef ENGINE_H
#define ENGINE_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "game_board.h"
#include "token.h"
#include <memory>

class Engine : public sf::Drawable
{
public:
    Engine(const unsigned int & p):board(p){}
    void main_game_loop(sf::RenderWindow & window);
    void gen(std::vector <bool> & loop_controls,sf::RenderWindow & window);
    friend class laid_Token;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(board, states);
        for(auto & x : vectok)
        {
            if(x != NULL)
                target.draw(*x,states);
        }
    }
    void align_tokens(sf::RenderWindow & window);
    game_board board;
    std::vector <std::unique_ptr<Token>> vectok ;
    sf::Event event;
    sf::Clock clock;
};

#endif // ENGINE_H
