#ifndef SETINGS_H
#define SETINGS_H
#include "button.h"
#include "SFML/Graphics/Font.hpp"
#include "texture_pack.h"
#include <windows.h>
class setings: public sf::Drawable
{
public:
    setings(Texture_pack &t);
    bool setings_click(sf::RenderWindow &window, Texture_pack &t);
    static bool displayChoiceWindow(const std::string &tex, sf::Font & font, sf::Texture &t, sf::Image &I, const std::string& title = "Are you Sure?" );
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;
    static std::string getInputFromWindow(sf::Font & font, sf::Image &I, const std::string& title);
protected:
    std::unique_ptr <Button> Back_to_menu_button;
    std::unique_ptr <Button> Info_button;
};

#endif // SETINGS_H
