#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player : public Animation
{
private:
public:
	Player(void);
	Player(const std::string source, std::vector<sf::IntRect>& textureRects);
	Player(std::string source);
	~Player();

};

