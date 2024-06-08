#ifndef TEXTURE_PACK_H
#define TEXTURE_PACK_H

#include "SFML/Graphics/Texture.hpp"
class Texture_pack
{
public:
    Texture_pack();
    bool load_textures();
    sf::Texture Two_P;
    sf::Texture Three_P;
    sf::Texture Four_P;

};

#endif // TEXTURE_PACK_H
