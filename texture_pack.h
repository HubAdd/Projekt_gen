#ifndef TEXTURE_PACK_H
#define TEXTURE_PACK_H

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Audio.hpp>
class Texture_pack
{
public:
    Texture_pack();
    bool load_textures();

    sf::Font font;
    sf::Font font1;

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

    sf::SoundBuffer boop;
    sf::SoundBuffer void_;
    sf::SoundBuffer genius;
    sf::SoundBuffer party;
    sf::SoundBuffer street;
    sf::SoundBuffer guitar;
    sf::SoundBuffer RIO;

    std::vector <sf::Texture> logo_animation;


};

#endif // TEXTURE_PACK_H
