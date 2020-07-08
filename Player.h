#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Animation.h"
#include "AI.h"

class Player : public Animation, public AI
{
private:
	sf::Vector2f m_size;
public:
	Player(void);
	Player(RessourceManager &manager);
	Player(const std::string source, std::vector<sf::IntRect>& textureRects, RessourceManager &manager);
	Player(std::string source, RessourceManager &manager);
	~Player();

	virtual bool onClick(sf::RenderWindow*& window);
	virtual void move();
};

