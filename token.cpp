#include "token.h"
#include "additionalshapedecorator.h"
#include <cmath>

Token::Token(float size):sf::Drawable(){

    token_pair = {std::make_unique<sextangle>(size),std::make_unique<sextangle>(size)};
    token_pair.first->setFillColor(sf::Color::Black);
    token_pair.second->setFillColor(sf::Color::Black);


};


void Token::move(const sf::RenderWindow & window)
{
    sf::Vector2f move_vec = {static_cast<float>(sf::Mouse::getPosition(window).x),static_cast<float>(sf::Mouse::getPosition(window).y)};
    align(move_vec);
}
void Token::align(const sf::Vector2f & move_vec)
{
    static_cast<AdditionalShapeDecorator*>(token_pair.first.get())->setposition({static_cast<float>(move_vec.x),static_cast<float>(move_vec.y)});
    auto rotateVector = [](const sf::Vector2f & vec, double angleDegrees) {
        double angleRadians = angleDegrees * M_PI / 180.0;
        double cosAngle = std::cos(angleRadians);
        double sinAngle = std::sin(angleRadians);

        sf::Vector2f rotatedVec;
        rotatedVec.x = vec.x * cosAngle - vec.y * sinAngle;
        rotatedVec.y = vec.x * sinAngle + vec.y * cosAngle;

        return rotatedVec;
    };
    auto z = sf::Vector2f({0,static_cast<float>(token_pair.first->h*2.05)});
    auto s = rotateVector(z, rotation*60);
    static_cast<AdditionalShapeDecorator*>(token_pair.second.get())->setposition(move_vec+s);
}
std::pair <sf::Color,sf::Color> Token::get_Color () {return {static_cast<AdditionalShapeDecorator*>(token_pair.first.get())->get_color_(),static_cast<AdditionalShapeDecorator*>(token_pair.second.get())->get_color_()};}
std::pair <unsigned int, unsigned int> Token::get_types () {return {static_cast<AdditionalShapeDecorator*>(token_pair.first.get())->get_type_(),static_cast<AdditionalShapeDecorator*>(token_pair.second.get())->get_type_()};}
void Token::token_switch(const unsigned int & type1, const unsigned int & type2)
{
    auto s1 = std::move(token_pair.first);
    auto s2 = std::move(token_pair.second);
    token_pair.first = std::make_unique<AdditionalShapeDecorator>(std::move(s1),type1);
    token_pair.second = std::make_unique<AdditionalShapeDecorator>(std::move(s2),type2);
}
void Token::rotate()
{
    if(rotation == 5)
        rotation = 0;
    else
        rotation++;
}
bool Token::mouse_on_token(sf::RenderWindow &window)
{
    return token_pair.first->mouse_on(window) || token_pair.second->mouse_on(window);
}

