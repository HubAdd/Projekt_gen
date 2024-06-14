#ifndef TEXTURE_PACK_H
#define TEXTURE_PACK_H

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Audio.hpp>
class Texture_pack
{
public:
    Texture_pack();

    //ładowanie tekstur, jeśli da false, gra się nie zaczyna
    bool load_textures();

    //pakiet czcionek
    sf::Font font;
    sf::Font font1;

    //pakiet obrazów
    sf::Texture Two_P;
    sf::Texture Three_P;
    sf::Texture Four_P;
    sf::Texture Player_One;
    sf::Texture Player_Two;
    sf::Texture Player_Three;
    sf::Texture Player_Four;
    sf::Texture screen_;
    sf::Texture main_screen;
    sf::Texture metal;
    sf::Texture gold;

    sf::Image icon;


    //pakiet dźwięków
    sf::SoundBuffer boop;
    sf::SoundBuffer void_;
    sf::SoundBuffer genius;
    sf::SoundBuffer party;
    sf::SoundBuffer street;
    sf::SoundBuffer guitar;
    sf::SoundBuffer RIO;

    //wektor tekstur loga (potrzebne do animacji)
    std::vector <sf::Texture> logo_animation;


};

#endif // TEXTURE_PACK_H
