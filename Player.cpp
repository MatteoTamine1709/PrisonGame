#include <iostream>
#include "Player.h"

Player::Player(void)
	: Animation("PlayerSkin.png")
{

}

Player::Player(const std::string source, std::vector<sf::IntRect>& textureRects)
	: Animation(source, textureRects)
{
}

Player::Player(const std::string source)
	: Animation(source)
{
}

Player::~Player()
{
	std::cout << "Delete Player" << std::endl;
}