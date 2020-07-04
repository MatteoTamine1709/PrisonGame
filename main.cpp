#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "HUD.h"

int main()
{
    Game game;
    std::vector<sf::IntRect> rects = { {0, 238, 100, 105}, {102, 238, 100, 105}, {200, 238, 100, 105}, {306, 238, 100, 105} };
    Player player("PlayerSkin.png", game.ressourceManager);
    Player player1("PlayerSkin.png", game.ressourceManager);
    Player player2("PlayerSkin.png", game.ressourceManager);
    Player player3("PlayerSkin.png", game.ressourceManager);
    HUD hud;
    Button button({ 0, 0 }, { 100, 30 }, "Button 1");
    hud.push_button(button);
    game.push_hud("Test", hud);
    button.setTick(500);
    player.setTexture("AnimationTest.png");
    player3.setTexture("AnimationTest.png");
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