#include "Animation.h"
#include <iostream>

void Animation::setTexture(const std::string& str)
{
	int i = 0;

	for (i = 0; i < ressourceManager->texturePair.size(); i++)
		if (ressourceManager->texturePair[i].first.compare(str) == 0) {
			m_texture = ressourceManager->texturePair[i].second;
			break;
		}
	if (i == ressourceManager->texturePair.size()) {
		m_texture = new sf::Texture();
		m_texture->loadFromFile(str);
		ressourceManager->add(str, m_texture);
	}
	m_sprite.setTexture(*m_texture);
}

Animation::Animation(const std::string source, std::vector<sf::IntRect> &textureRects, RessourceManager& manager)
	: m_textureRects(textureRects), ressourceManager(&manager)
{
	setTexture(source);
	m_sprite.setTexture(*m_texture);
	m_sprite.setTextureRect(textureRects[0]);
}

Animation::Animation(std::string source, RessourceManager& manager)
	: ressourceManager(&manager)
{
	setTexture(source);
	m_sprite.setTexture(*m_texture);
}

Animation::~Animation()
{

}

void Animation::setTickUpdate(int tick)
{
	m_tickUpdate = tick;
}

void Animation::update(void)
{
	m_tickCounter++;
	if (m_tickUpdate != m_tickCounter || m_textureRects.size() == 0 || m_textureRects.size() == 1)
		return;
	m_tickCounter = 0;
	m_rectIndex++;
	if (m_rectIndex >= m_textureRects.size())
		m_rectIndex = 0;
	m_sprite.setTextureRect(m_textureRects[m_rectIndex]);
}

void Animation::setPosition(const sf::Vector2f& pos)
{
	m_sprite.setPosition(pos);
}

void Animation::draw(sf::RenderWindow* &window)
{
	window->draw(m_sprite);
}