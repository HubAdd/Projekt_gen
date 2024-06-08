#include "texture_pack.h"

Texture_pack::Texture_pack() {}

bool Texture_pack::load_textures()
{
    if(!Two_P.loadFromFile("Two_P.png"))
        return false;
    if(!Three_P.loadFromFile("Three_P.png"))
        return false;
    if(!Four_P.loadFromFile("Four_P.png"))
        return false;
    return true;
}

