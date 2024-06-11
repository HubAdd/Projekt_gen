#include "setings.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"


setings::setings(Texture_pack & t)
{
    Back_to_menu_button = std::make_unique <Button> (sf::Vector2f(0,-20),t.Three_P,t.font,"Menu",0.1);
    Back_to_menu_button.get()->text.setFillColor(sf::Color::White);
    Back_to_menu_button.get()->text.move(0,-10);

    Info_button = std::make_unique <Button> (sf::Vector2f(Back_to_menu_button.get()->react.getGlobalBounds().width,-20),t.Three_P,t.font,"Info",0.1);
    Info_button.get()->text.setFillColor(sf::Color::White);
    Info_button.get()->text.move(0,-10);

}

bool setings::setings_click(sf::RenderWindow & window_, Texture_pack & t)
{
    bool result = false;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(Back_to_menu_button->mouse_on(window_))
            result = displayChoiceWindow("Progress will be lost",t.font,t.metal,t.icon);


        if(Info_button->mouse_on(window_))
        {
            // Tworzenie okna
            sf::RenderWindow window(sf::VideoMode(600, 300), "Game Info", sf::Style::Titlebar | sf::Style::Close);

            window.setIcon(t.icon.getSize().x,t.icon.getSize().y,t.icon.getPixelsPtr());

            // Pobieranie uchwytu okna
            HWND hwnd = window.getSystemHandle();

            // Ustawienie okna na zawsze na wierzchu
            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

            // Tworzenie tekstów dla opcji

            sf::RectangleShape rec;
            rec.setTexture(&t.gold);
            rec.setSize({600,300});
            rec.setPosition({0,0});

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        result = false;
                    }


                }

                window.clear();
                window.draw(rec);
                window.display();
            }
        }
    }
    return result;
}

void setings::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*Back_to_menu_button.get() , states);
    target.draw(*Info_button.get() , states);
}

bool setings::displayChoiceWindow(const std::string& tex, sf::Font & font , sf::Texture & t, sf::Image &I, const std::string& title) {

    // Tworzenie okna
    sf::RenderWindow window(sf::VideoMode(300, 150), title, sf::Style::Titlebar | sf::Style::Close);

    window.setIcon(I.getSize().x,I.getSize().y,I.getPixelsPtr());

    // Pobieranie uchwytu okna
    HWND hwnd = window.getSystemHandle();

    // Ustawienie okna na zawsze na wierzchu
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    // Tworzenie tekstów dla opcji

    sf::RectangleShape rec;
    rec.setTexture(&t);
    rec.setSize({300,150});
    rec.setPosition({0,0});

    sf::Text Text(tex, font, 16);
    Text.setFillColor(sf::Color::Black);
    Text.setPosition(5, 5);

    sf::Text yesText("Yes", font, 20);
    yesText.setFillColor(sf::Color::Black);
    yesText.setPosition(75, 50);

    sf::Text noText("No", font, 20);
    noText.setFillColor(sf::Color::Black);
    noText.setPosition(175, 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (yesText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

                        window.close();
                        return true;
                    }
                    if (noText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

                        window.close();
                        return false;
                    }
                }
            }
        }

        window.clear();
        window.draw(rec);
        window.draw(yesText);
        window.draw(noText);
        window.draw(Text);
        window.display();
    }

    return false; // Default value if window is closed without selection
}

std::string setings::getInputFromWindow(sf::Font & font, sf::Image &I, const std::string& title) {
    sf::RenderWindow window(sf::VideoMode(400, 200), title);

    window.setIcon(I.getSize().x,I.getSize().y,I.getPixelsPtr());

    // Pobieranie uchwytu okna
    HWND hwnd = window.getSystemHandle();

    // Ustawienie okna na zawsze na wierzchu
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    sf::Text text("", font, 24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 80);

    std::string input;
    bool enterPressed = false;

    while (window.isOpen() && !enterPressed) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b') { // Handle backspace
                        if (!input.empty()) {
                            input.pop_back();
                        }
                    } else if (event.text.unicode == '\r') { // Handle enter
                        enterPressed = true;
                    } else if (input.size() < 12) {
                        input += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }

        text.setString(input + "_");
        window.clear();
        window.draw(text);
        window.display();
    }

    window.close();
    return input;
}
