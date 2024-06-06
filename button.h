#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#ifndef BUTTON_H
#define BUTTON_H

class Button: public sf::Drawable {
private:
    sf::Sprite sprite;         // Sprite przycisku
    sf::Text text;             // Tekst na przycisku
    sf::Texture texture;       // Tekstura przycisku


public:
    Button();
    // Konstruktor przyjmujący pozycję, teksturę oraz tekst
    Button(const sf::Vector2f& position, const std::string& texturePath, const std::string& buttonText);


    // Metoda do rysowania przycisku na oknie
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Metoda do sprawdzania, czy myszka jest nad przyciskiem
    bool mouse_on(const sf::Vector2f& mousePosition);



};

#endif // BUTTON_H
