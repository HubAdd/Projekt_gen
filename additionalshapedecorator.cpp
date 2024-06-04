#include "additionalshapedecorator.h"
#include "_circle_shape.h"
#include "hexagon.h"
#include "hollowcircleshape.h"
#include "starshape.h"
#include "starshape1.h"
#include "starshape2.h"

AdditionalShapeDecorator::AdditionalShapeDecorator(std::unique_ptr<sextangle> mainShape, const unsigned int &type)
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
    this->setFillColor(sf::Color::Black);
}



void AdditionalShapeDecorator::setposition (sf::Vector2f pos){

    setPosition(pos);
    if(static_cast <CustomShape*>(additionalShape_.get())->get_type() == 5 || static_cast <CustomShape*>(additionalShape_.get())->get_type() == 6)
        additionalShape_->setPosition(pos);
    else
    {
    pos-=sf::Vector2f(this->h_()*0.75,this->h_()*0.75);
    additionalShape_->setPosition(pos);
    }
}
sf::Color AdditionalShapeDecorator::get_color_(){if(additionalShape_->getFillColor() != sf::Color::Transparent){return additionalShape_->getFillColor();}else{return additionalShape_->getOutlineColor();}}
unsigned int AdditionalShapeDecorator::get_type_ () {return static_cast <CustomShape*>(additionalShape_.get())->get_type();}
