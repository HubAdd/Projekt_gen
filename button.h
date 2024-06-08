#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#ifndef BUTTON_H
#define BUTTON_H

class Button {
private:
    sf::Sprite sprite;         // Sprite przycisku
    sf::RectangleShape react;  // HitBox przycisku


public:
    Button();
    // Konstruktor przyjmujący pozycję, teksturę oraz tekst
    Button(const sf::Vector2f & position, sf::Texture & texture_);


    // Metoda do rysowania przycisku na oknie
    void draw(sf::RenderWindow & window);

    // Metoda do sprawdzania, czy myszka jest nad przyciskiem
    bool mouse_on(sf::RenderWindow & window);

    int get_num();

};

#endif // BUTTON_H
