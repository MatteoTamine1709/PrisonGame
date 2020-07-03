#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    Game game;
    std::vector<sf::IntRect> rects = { {0, 238, 100, 105}, {102, 238, 100, 105}, {200, 238, 100, 105}, {306, 238, 100, 105} };
    Player player("AnimationTest.png", rects);
    player.setTickUpdate(30);
    game.push_animation(player);
    game.run();
}