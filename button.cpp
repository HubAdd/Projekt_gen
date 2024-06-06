#include "button.h"
#include <iostream>
#include <ostream>

Button::Button(){};
// Konstruktor przyjmujący pozycję, teksturę oraz tekst
Button::Button(const sf::Vector2f& position, const std::string& texturePath, const std::string& buttonText)
{

    // Ładowanie tekstury
    if (!texture.loadFromFile(texturePath)) {
        std::cerr<<"Error loading texture"<<std::endl;

    }

    // Ustawienie sprite'a przycisku
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.2f, 0.2f);
    // Ustawienie tekstu na przycisku
    text.setString(buttonText);
    sf::Font font;
    if(font.loadFromFile("fonti.ttf"))
        text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + (sprite.getLocalBounds().width - text.getGlobalBounds().width) / 2, position.y + (sprite.getLocalBounds().height - text.getGlobalBounds().height) / 2);
}

// Metoda do rysowania przycisku na oknie
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(text,states);
    target.draw(sprite,states);

}

// Metoda do sprawdzania, czy myszka jest nad przyciskiem
bool Button::mouse_on(const sf::Vector2f& mousePosition) {
    if (sprite.getGlobalBounds().contains(mousePosition)) {

        return true;
    } else {

        return false;
    }
}
