#ifndef TOKEN_H
#define TOKEN_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "sextangle.h"
class Token : public sf::Drawable
{
public:
    //kostruktor pobierający rozmiar sześciokątów, z których zostanie utworzony
    Token(float size);

    //nadpisanie metody draw
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;

    //zwraca pare z kolorami znaczków na tokenie
    std::pair <sf::Color,sf::Color> get_Color ();

    //zwraca pare z typami znaczków na tokenie
    std::pair <unsigned int, unsigned int> get_types ();

    //sprawdza czy myszka jest nad danym tokenem
    bool mouse_on_token(sf::RenderWindow &window);

    //ustawienie rotacjii tokena na 0
    void reset_rotation();

    //tylko klasy laid_Token i Engine mogą używac prywatnych metod Tokenów
    friend class laid_Token;
    friend class Engine;
private:
    std::pair <std::unique_ptr<sextangle>,std::unique_ptr<sextangle>> token_pair;
    unsigned int rotation = 0;

    //zmiania typów znaczków na tokenie
    void token_switch(const unsigned int & type1, const unsigned int & type2);

    //ustabilizowanie tokena miejscu wskazanym przez argument wejściowy
    void align(const sf::Vector2f & move_vec);

    //ruszanie tokenem, oba sześciokąty się ruszają i znaczki na nich też
    void move(const sf::RenderWindow & window);

    //inkrementacja rotacjii Tokena
    void rotate();

};

#endif // TOKEN_H
