#include <iostream>
#include "Player.h"

Player::Player(RessourceManager& manager)
	: Animation("PlayerSkin.png", manager)
{

}

Player::Player(const std::string source, std::vector<sf::IntRect>& textureRects, RessourceManager &manager)
	: Animation(source, textureRects, manager)
{
}

Player::Player(const std::string source, RessourceManager &manager)
	: Animation(source, manager)
{
}

Player::~Player()
{

}