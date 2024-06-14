#ifndef ADDITIONALSHAPEDECORATOR_H
#define ADDITIONALSHAPEDECORATOR_H

#include "sextangle.h"

//dekorator nakładający znaczek na sześciokąt
class AdditionalShapeDecorator : public sextangle
{
public:
    //konstruktor przyjmuje jako argument wskaźnik do kształtu,
    //na który bedzie nakładał drugi kształ, zależny od tego jaki type zostanie dany jako argument
    AdditionalShapeDecorator(std::unique_ptr<sextangle> mainShape, const unsigned int &type);

    //nadpisanie metody draw
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    //setposition ustawia pozycje zarówno kształu glównego, jak i nałożonego
    void setposition (sf::Vector2f pos);

    //zwraca kolor nałożonego ksztalu (funkcja potrzebna do animacji pokolorowanych krawędzi stykających się sześcianów)
    sf::Color get_color_();

    //zwraca typ nałożonego ksztalu (funkcja potrzebna do animacji pokolorowanych krawędzi stykających się sześcianów)
    unsigned int get_type_ ();
private:

    //wzkaźnik z dodatkowym kształtem
    std::unique_ptr<sf::Shape> additionalShape_;
};

#endif // ADDITIONALSHAPEDECORATOR_H
