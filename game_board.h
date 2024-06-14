#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "sextangle.h"

//klasa odpowiadająca za plansze
class game_board : public sf::Drawable
{
public:
    //domyślny konstruktor
    game_board();

    //konstruktor przyjmujący liczbe graczy
    game_board(const unsigned int &num):
        players_number_(num){}

    //funkcja która generuje planszę, przyjmuje okno gry jako argument, by dopasować wymiary sześciokątów
    void new_board(sf::RenderWindow &window);

    //nadpisana metoda draw
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    //funkcja resetująca linie sześciokątów (używana jest po zakończeniu animacjii podświetlania sąsiadujących tokenów )
    void reset_lines();

    //bool który sprawdza czy nie ma już miejsca planszy (jesli == true to koniec gry)
    bool no_space();

    //zwraca liczbę graczy
    unsigned int players_number(){return players_number_;}

    //zwraca wymiary sześciokątów na planszy
    float size_(){return size;}

    //deklaracja przyjaźni klasy laid_Token i Engine, bo działają one na vec1
    friend class laid_Token;
    friend class Engine;

private:
    //liczba graczy
    unsigned int players_number_;

    //wektor sześciokątów zawierających się w planszy
    std::vector <std::unique_ptr<sextangle>> vec1;

    //wymiary sześciokątów wchodzących w skład planszy
    float size;


};

#endif // GAME_BOARD_H
