#include <iostream>
#include <cmath>
#include "Player.h"

Player::Player(RessourceManager& manager)
	: Animation("PlayerSkin.png", manager)
{
	m_sprite.setPosition({ -m_sprite.getLocalBounds().width / 2, -m_sprite.getLocalBounds().height / 2 });
}

Player::Player(const std::string source, std::vector<sf::IntRect>& textureRects, RessourceManager &manager)
	: Animation(source, textureRects, manager)
{
	m_sprite.setPosition({ -m_sprite.getLocalBounds().width / 2, -m_sprite.getLocalBounds().height / 2 });
}

Player::Player(const std::string source, RessourceManager &manager)
	: Animation(source, manager)
{
	m_sprite.setPosition({ -m_sprite.getLocalBounds().width / 2, -m_sprite.getLocalBounds().height / 2 });
}

Player::~Player()
{

}

void Player::onClick(sf::RenderWindow *&window)
{
	m_destination = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	float d = dist(m_pos.x, m_pos.y, m_destination.x, m_destination.y);
	m_dir.x = (m_destination.x - m_pos.x) / d * m_speed;
	m_dir.y = (m_destination.y - m_pos.y) / d * m_speed;
}

void Player::move()
{
	if (dist(m_pos.x, m_pos.y, m_destination.x, m_destination.y) > m_speed) {
		m_pos += m_dir;
		m_sprite.move(m_dir);
	} else {
		m_dir = { 0, 0 };
	}
}
