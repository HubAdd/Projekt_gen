#ifndef SETINGS_H
#define SETINGS_H
#include "button.h"
#include "SFML/Graphics/Font.hpp"
#include "texture_pack.h"
#include <windows.h>
class Engine;
class setings: public sf::Drawable
{
public:
    setings(Texture_pack &t);
    void setings_click(Engine &E);
    void setSoundFromWindow(Texture_pack &t, sf::Sound &s);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;
    static std::string getInputFromWindow(sf::Font & font, sf::Image &I, const std::string& title);
    static bool displayChoiceWindow(const std::string &tex, sf::Font & font, sf::Texture &t, sf::Image &I, const std::string& title = "Are you Sure?" );
protected:
    std::unique_ptr <Button> Back_to_menu_button;
    std::unique_ptr <Button> Info_button;
    std::unique_ptr <Button> Reset_button;
    std::unique_ptr <Button> Music_button;
};

#endif // SETINGS_H
