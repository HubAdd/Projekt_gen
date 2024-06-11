#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"
#ifndef BUTTON_H
#define BUTTON_H

class Button: public sf::Drawable {
private:
    sf::Sprite sprite;         // Sprite przycisku
    sf::RectangleShape react;  // HitBox przycisku
    sf::Text text;
    friend class Menu;
    friend class setings;

public:
    Button();
    // Konstruktor przyjmujący pozycję, teksturę oraz tekst
    Button(const sf::Vector2f & position, sf::Texture & texture_, sf::Font & font, const std::string & button_text, const float &scale);

    // Metoda do rysowania przycisku na oknie
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;

    // Metoda do sprawdzania, czy myszka jest nad przyciskiem
    bool mouse_on(sf::RenderWindow & window);

    int get_num();

};

#endif // BUTTON_H
