#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"

class Game
{
private:
	sf::RenderWindow* m_window;
	virtual void handleEvent(void);
	virtual void fixedUpdate(void);
	virtual void update(void);
	virtual void render(void);
	std::vector<Animation> m_animations;
	std::vector<std::pair<std::string, sf::Texture>> texturePair;

public:
	Game();
	~Game();

	virtual void run(void);
	virtual void push_animation(Animation& animation);
};

