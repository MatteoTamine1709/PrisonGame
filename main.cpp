#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "HUD.h"
#include "Windows.h"
#include "Log.h"
#include "main.h"

Log LOG = Log();

int main()
{
    LOG.setLogLevel(LogLevel_e::All);
    sf::err().rdbuf(NULL);
    Game game({ 1920, 960 }, 60, "Prison Game");
    Animation map("Map.jpg", game.ressourceManager);
    game.push_animation(map);
    game.run();
}