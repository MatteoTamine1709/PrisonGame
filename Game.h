#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"
#include "HUD.h"

class Game
{
private:
	sf::RenderWindow* m_window;
	sf::View m_view;
	virtual void handleEvent(void);
	virtual void fixedUpdate(void);
	virtual void update(void);
	virtual void render(void);
	std::vector<Animation> m_animations;
	std::vector<std::pair<const std::string *, HUD *>> m_HUDS;
	HUD* m_currentHUD = nullptr;

public:
	Map* map;
	RessourceManager ressourceManager;
	Player player = Player("PlayerSkin.png", ressourceManager);

	Game();
	Game(sf::Vector2u size, unsigned frameRate, const char *windowName);
	~Game();

	virtual void run(void);
	virtual void push_animation(Animation& animation);
	virtual void push_hud(const std::string& name, HUD& hud);
	virtual void changeHUD(const std::string& name);
};

