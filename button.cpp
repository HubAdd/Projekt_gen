#include "button.h"
#include "SFML/Window/Mouse.hpp"


Button::Button(){};
// Konstruktor przyjmujący pozycję, teksturę oraz tekst
Button::Button(const sf::Vector2f& position, sf::Texture & texture_, sf::Font &font, const std::string & button_text, const float & scale)
{

    // Ładowanie tekstury

    text.setFont(font);
    text.setString(button_text);
    text.setCharacterSize(37);
    text.setFillColor(sf::Color::Black);

    // Ustawienie sprite'a przycisku
    sprite.setTexture(texture_);

    react = sf::RectangleShape({static_cast<float>(sprite.getLocalBounds().width*scale),static_cast<float>(sprite.getLocalBounds().height*scale)});
    react.setPosition(position);
    text.setPosition(position.x + (react.getLocalBounds().width - text.getGlobalBounds().width) / 2, position.y + (react.getLocalBounds().height - text.getGlobalBounds().height) / 2.5);

    sprite.setPosition(position);
    //sprite.setTextureRect(sf::IntRect(50, 50, 50, 50));
    sprite.setScale(scale,scale);
    // Ustawienie tekstu na przycisku

}

// Metoda do rysowania przycisku na oknie
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite,states);
    target.draw(text);
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


