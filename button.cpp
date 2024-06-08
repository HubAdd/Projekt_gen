#include "button.h"
#include "SFML/Window/Mouse.hpp"


Button::Button(){};
// Konstruktor przyjmujący pozycję, teksturę oraz tekst
Button::Button(const sf::Vector2f& position, sf::Texture & texture_)
{

    // Ładowanie tekstury


    // Ustawienie sprite'a przycisku
    sprite.setTexture(texture_);

    react = sf::RectangleShape({static_cast<float>(sprite.getLocalBounds().width*0.25),static_cast<float>(sprite.getLocalBounds().height*0.25)});
    react.setPosition(position);

    sprite.setPosition(position);
    //sprite.setTextureRect(sf::IntRect(50, 50, 50, 50));
    sprite.setScale(0.25f,0.25f);
    // Ustawienie tekstu na przycisku

}

// Metoda do rysowania przycisku na oknie
void Button::draw(sf::RenderWindow & window)
{


    window.draw(sprite);

}

// Metoda do sprawdzania, czy myszka jest nad przyciskiem
bool Button::mouse_on(sf::RenderWindow & window) {
    sf::Vector2f vec = {static_cast<float>(sf::Mouse::getPosition(window).x),static_cast<float>(sf::Mouse::getPosition(window).y)};
    if (react.getGlobalBounds().contains(vec)) {

        return true;
    } else {

        return false;
    }
}

int Button::get_num(){return (react.getPosition().y-200)/100;}
