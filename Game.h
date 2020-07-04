#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"
#include "HUD.h"

class Game
{
private:
	sf::RenderWindow* m_window;
	virtual void handleEvent(void);
	virtual void fixedUpdate(void);
	virtual void update(void);
	virtual void render(void);
	std::vector<Animation> m_animations;
	std::vector<std::pair<const std::string *, HUD *>> m_HUDS;
	HUD* m_currentHUD = nullptr;

public:
	RessourceManager ressourceManager;

	Game();
	~Game();

	virtual void run(void);
	virtual void push_animation(Animation& animation);
	virtual void push_hud(const std::string& name, HUD& hud);
	virtual void changeHUD(const std::string& name);
};

