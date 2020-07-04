#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "HUD.h"
#include "Windows.h"
#include "Log.h"

Log LOG = Log();

int main()
{
    sf::err().rdbuf(NULL);
    LOG.setLogLevel(LogLevel_e::Warning);
    Game game;
    std::vector<sf::IntRect> rects = { {0, 238, 100, 105}, {102, 238, 100, 105}, {200, 238, 100, 105}, {306, 238, 100, 105} };
    Player player("PlayerSkin.png", game.ressourceManager);
    Player player1("PlayerSkin.png", game.ressourceManager);
    Player player2("PlayerSkin.png", game.ressourceManager);
    Player player3("PlayerSkin.png", game.ressourceManager);
    HUD hud;
    Button button(game.ressourceManager, { 0, 0 }, { 100, 30 }, "Button 1", "PlayerSkin.png");
    Button button2(game.ressourceManager, { 200, 0 }, { 100, 30 }, "Button 2", sf::Color::Red);
    hud.push_button(button);
    hud.push_button(button2);
    game.push_hud("Test", hud);
    player1.setPosition({ 200, 0 });
    player2.setPosition({ 400, 0 });
    player3.setPosition({ 0, 200 });
    player.setTickUpdate(30);
    player.setTexture("AnimatiEonTest.png");
    player3.setTexture("AnimationTest.png");
    game.push_animation(player);
    game.push_animation(player1);
    game.push_animation(player2);
    game.push_animation(player3);
    game.run();
}