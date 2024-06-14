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

    //obsługa kliknięcia przycisków w setingsach
    void setings_click(Engine &E);

    //otworzenie okna wyboru dźwięku
    void setSoundFromWindow(Texture_pack &t, sf::Sound &s);

    //nadpisanie metody draw
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;

    //statyczna metoda wyświetlająca okno gdzie można wpisać stringa
    static std::string getInputFromWindow(sf::Font & font, sf::Image &I, const std::string& title);

    //statyczna metoda wyświetlająca okno gdzie można wybrac opcje tak lub nie
    static bool displayChoiceWindow(const std::string &tex, sf::Font & font, sf::Texture &t, sf::Image &I, const std::string& title = "Are you Sure?" );
protected:
    //przycisk powrotu do menu
    std::unique_ptr <Button> Back_to_menu_button;

    //przycisk info
    std::unique_ptr <Button> Info_button;

    //przycisk resetu
    std::unique_ptr <Button> Reset_button;

    //przycisk obsługi muzyki
    std::unique_ptr <Button> Music_button;
};

#endif // SETINGS_H
