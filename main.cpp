#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Map.h"
#include "HUD.h"
#include "Log.h"
#include "AI.h";

Log LOG = Log();

int main()
{
    LOG.setLogLevel(LogLevel_e::Info);
    sf::err().rdbuf(NULL);
    std::vector<std::vector<int>> grid =
    {
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    };
    Map map(grid.size(), grid[0].size(), grid);
    Game game({ 1920, 960 }, 60, "Prison Game");
    game.map = &map;
    Animation mapText("Map.jpg", game.ressourceManager);
    Animation p("PlayerSkin.png", game.ressourceManager);
    game.push_animation(mapText);
    game.push_animation(p);
    game.run();
}