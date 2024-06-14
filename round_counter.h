#ifndef ROUND_COUNTER_H
#define ROUND_COUNTER_H
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "texture_pack.h"

//licznik rund
//RUNDA - informacja którego gracza jest kolej
class Round_Counter : public sf::Drawable
{
public:
    //przyjmuje tekstury jako argument konstruktora by założyć na sprite te tekstury
    Round_Counter(sf::Texture & t);

    //nadpisana metoda draw
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;

    //zwraca info ktora jest runda
    unsigned int get_round();

    //zwiększa info o rundzie o 1, chyba ze wychodzi poza zakres liczby graczy, to wtedy cofa
    void add_round(const unsigned int &p_num, Texture_pack & t);

private:
    //sprite na którym są poszczególne teksttury
    sf::Sprite sprite;

    //info która jest runda
    unsigned int round;
};

#endif // ROUND_COUNTER_H
