#ifndef ADDITIONALSHAPEDECORATOR_H
#define ADDITIONALSHAPEDECORATOR_H

#include "sextangle.h"

class AdditionalShapeDecorator : public sextangle
{
public:
    AdditionalShapeDecorator(std::unique_ptr<sextangle> mainShape, const unsigned int &type);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setposition (sf::Vector2f pos);
    sf::Color get_color_();
    unsigned int get_type_ ();
private:

    std::unique_ptr<sf::Shape> additionalShape_;
};

#endif // ADDITIONALSHAPEDECORATOR_H
