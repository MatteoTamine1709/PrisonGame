#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player : public Animation
{
private:
public:
	Player(RessourceManager &manager);
	Player(const std::string source, std::vector<sf::IntRect>& textureRects, RessourceManager &manager);
	Player(std::string source, RessourceManager &manager);
	~Player();

};

