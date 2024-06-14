#ifndef SEXTANGLE_H
#define SEXTANGLE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class sextangle : public sf::ConvexShape
{
public:
    //konstruktor ktory przyjmuje rozmiar sześciokąta
    sextangle(const float &size);

    //metoda sprawdzająca czy myszka jest nad danym sześciokątem
    bool mouse_on (const sf::RenderWindow & window);

    //metoda sprawdzająca czy dany wektor jest nad danym sześciokątem
    bool vec_on (const sf::Vector2i &vec);

    //metoda obliczająca i zwracająca 1/2 wysokość sześciokąta
    float h_();

    //deklaracja przyjaźni token (klasa token zmienia kolor sześciokąta)
    friend class Token;

};

#endif // SEXTANGLE_H
