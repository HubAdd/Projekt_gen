#include "additionalshapedecorator.h"
#include "_circle_shape.h"
#include "hexagon.h"
#include "hollowcircleshape.h"
#include "starshape.h"
#include "starshape1.h"
#include "starshape2.h"

AdditionalShapeDecorator::AdditionalShapeDecorator(std::unique_ptr<sextangle> mainShape, const unsigned int &type)

    //bierze jako argument główny sześcian i ozdabia go w zależności od int type

    : sextangle(static_cast<sextangle>(*mainShape)) {
    switch (type) {
    case 1:
        additionalShape_ = std::make_unique<StarShape>(this->h_()*0.75);
        break;
    case 2:
        additionalShape_ = std::make_unique<StarShape1>(this->h_()*0.75);
        break;
    case 3:
        additionalShape_ = std::make_unique<StarShape2>(this->h_()*0.75);
        break;
    case 4:
        additionalShape_ = std::make_unique<HollowCircleShape>(this->h_()*0.75);
        break;
    case 5:
        additionalShape_ = std::make_unique<Hexagon>(this->h_()*0.75);
        break;
    case 6:
        additionalShape_ = std::make_unique<_Circle_Shape>(this->h_()*0.75);
        break;
    default:
        break;
    }
    //Sześciokąt po ozdobieniu zawsze jest czarny, bo nzaczy to, że jest częścią tokena, położonego bądź nie
    this->setFillColor(sf::Color::Black);
}



void AdditionalShapeDecorator::setposition (sf::Vector2f pos){

    //zmienia pozycje głównego kształtu
    setPosition(pos);

    //zmienia pozycje dodanego kształtu

    //typy 5 i 6 mają inny punkt zaczepienia niż pozostałe znaczki, więc musialy zostać użyte inne współrzędne
    if(static_cast <CustomShape*>(additionalShape_.get())->get_type() == 5 || static_cast <CustomShape*>(additionalShape_.get())->get_type() == 6)
        additionalShape_->setPosition(pos);
    else
    {
    //zmiana wektora pos, adekwatna dla znaczków od 1 do 4
    pos-=sf::Vector2f(this->h_()*0.75,this->h_()*0.75);
    additionalShape_->setPosition(pos);
    }
}
//zwraca kolor znaczka, albo kolor wypełnienia, albo kolor obramowania, tak musi byc w przypadku znaczka fioletowego okręgu
sf::Color AdditionalShapeDecorator::get_color_(){if(additionalShape_->getFillColor() != sf::Color::Transparent){return additionalShape_->getFillColor();}else{return additionalShape_->getOutlineColor();}}

//zwraca typ znaczka
unsigned int AdditionalShapeDecorator::get_type_ () {return static_cast <CustomShape*>(additionalShape_.get())->get_type();}

//rysuje główny kształt i dodatkowy
void AdditionalShapeDecorator::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(static_cast<sextangle>(*this));
    target.draw(*additionalShape_, states);
}
