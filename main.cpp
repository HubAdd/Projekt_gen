#include "engine.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>






int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "InGenious");
    Engine E(4);
    E.main_game_loop(window);















    return 0;
}
