#include <iostream>
#include <cmath>
#include "Player.h"
#include "Log.h"

Player::Player(void)
{
}

Player::Player(RessourceManager& manager)
	: Animation("PlayerSkin.png", manager)
{
	m_size = { m_sprite.getLocalBounds().width, m_sprite.getLocalBounds().height };
	m_sprite.setPosition({ Pos.x - m_size.x / 2, Pos.y - m_size.y / 2 });
}

Player::Player(const std::string source, std::vector<sf::IntRect>& textureRects, RessourceManager &manager)
	: Animation(source, textureRects, manager)
{
	m_size = { m_sprite.getLocalBounds().width, m_sprite.getLocalBounds().height };
	m_sprite.setPosition({ Pos.x - m_size.x / 2, Pos.y - m_size.y / 2 });
}

Player::Player(const std::string source, RessourceManager &manager)
	: Animation(source, manager)
{
	m_size = { m_sprite.getLocalBounds().width, m_sprite.getLocalBounds().height };
	m_sprite.setPosition({ Pos.x - m_size.x / 2, Pos.y - m_size.y / 2 });
}

Player::~Player()
{

}

bool Player::onClick(sf::RenderWindow*& window)
{
	Pos.x = Dest.x;
	Pos.y = Dest.y;
    Dest.x = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y;
    Dest.y = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x;
	return (true);
}

void Player::move()
{
	AI::move();
	m_sprite.setPosition({ Pos.x - m_size.x / 2, Pos.y - m_size.y / 2 });
}
