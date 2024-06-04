#ifndef TOKEN_H
#define TOKEN_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "sextangle.h"
class Token : public sf::Drawable
{
public:
    Token(float size);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(*token_pair.first, states);
        target.draw(*token_pair.second, states);
    }
    void move(const sf::RenderWindow & window);
    void align(const sf::Vector2f & move_vec);
    void rotate();
    std::pair <sf::Color,sf::Color> get_Color ();
    std::pair <unsigned int, unsigned int> get_types ();
    void token_switch(const unsigned int & type1, const unsigned int & type2);
    bool mouse_on_token(sf::RenderWindow &window);
    void reset_rotation(){rotation =0;};
    friend class laid_Token;
private:
    std::pair <std::unique_ptr<sextangle>,std::unique_ptr<sextangle>> token_pair;
    unsigned int rotation = 0;

};

#endif // TOKEN_H
