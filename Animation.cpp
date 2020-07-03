#include "Animation.h"

Animation::Animation(const std::string source, std::vector<sf::IntRect> &textureRects)
	: m_textureRects(textureRects)
{
	m_texture.loadFromFile(source);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(textureRects[0]);
}

Animation::Animation(std::string source)
{
	m_texture.loadFromFile(source);
	m_sprite.setTexture(m_texture);
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

void Animation::draw(sf::RenderWindow *&window)
{
	window->draw(m_sprite);
}