#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Animation.h"

class Player : public Animation
{
private:
	sf::Vector2f m_pos = { 0, 0 };
	sf::Vector2f m_dir = { 0, 0 };
	sf::Vector2f m_destination;
	float m_speed = 5;
public:
	Player(RessourceManager &manager);
	Player(const std::string source, std::vector<sf::IntRect>& textureRects, RessourceManager &manager);
	Player(std::string source, RessourceManager &manager);
	~Player();

	virtual void onClick(sf::RenderWindow*& window);
	virtual void move();

};

