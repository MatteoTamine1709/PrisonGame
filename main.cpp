#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Map.h"
#include "HUD.h"
#include "Log.h"
#include "AI.h";
#include "FPSCounter.h"

Log LOG = Log();

int main()
{
    LOG.setLogLevel(LogLevel_e::Info);
    sf::err().rdbuf(NULL);
    sf::Image image;
    image.loadFromFile("Map.jpg");
    Arr2D grid = Map::convertImageToGrid(image);
    Map map(grid.size(), grid[0].size(), grid);
    Game game({ 1080, 720 }, 144, "Prison Game");
    game.setMap(&map);
    Animation mapText("Map.jpg", game.ressourceManager);
    Animation p("PlayerSkin.png", game.ressourceManager);
    game.push_animation(mapText);
    game.push_animation(p);
    game.run();
}