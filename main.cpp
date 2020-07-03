#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    Game game;
    std::vector<sf::IntRect> rects = { {0, 238, 100, 105}, {102, 238, 100, 105}, {200, 238, 100, 105}, {306, 238, 100, 105} };
    Player player("AnimationTest.png", rects, game.ressourceManager);
    Player player1("AnimationTest.png", rects, game.ressourceManager);
    Player player2("AnimationTest.png", rects, game.ressourceManager);
    Player player3("AnimationTest.png", rects, game.ressourceManager);
    player1.setPosition({ 200, 0 });
    player2.setPosition({ 400, 0 });
    player3.setPosition({ 0, 200 });
    player.setTickUpdate(30);
    game.push_animation(player);
    game.push_animation(player1);
    game.push_animation(player2);
    game.push_animation(player3);
    game.run();
}