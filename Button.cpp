#include "Button.h"
#include <iostream>

int defaultClickFuntion(void)
{
	std::cout << "Clicked\n";
	return 0;
}

Button::Button(sf::Vector2i pos, sf::Vector2f size, const std::string& name, sf::Color color)
	: m_pos(pos), m_size(size), m_name(name), m_function(&defaultClickFuntion)
{
	int charSize = 30;
	sf::Font *font = new sf::Font();

	font->loadFromFile("arial.ttf");
	m_text.setFont(*font);
	m_text.setString(name);
	while (charSize >= size.y)
		charSize /= 2;
	m_text.setCharacterSize(charSize);
	m_text.setFillColor(color);
	sf::FloatRect rect = m_text.getGlobalBounds();
	m_text.setPosition(rect.left + rect.width / 3, rect.top + rect.height / 3);

	m_rect.setPosition((sf::Vector2f) pos);
	m_rect.setSize(size);
	m_rect.setFillColor(m_idle_c);
}

Button::~Button(void)
{
	delete (m_text.getFont());
}

bool Button::onClick(sf::Vector2i mousePos)
{
	if (mousePos.x >= m_pos.x && mousePos.x <= m_pos.x + m_size.x &&
		mousePos.y >= m_pos.y && mousePos.y <= m_pos.y + m_size.y) {
		m_rect.setFillColor(m_clicked_c);
		m_tick = m_ClickTick;
		return (true);
	}
	return false;
}

void Button::update(void)
{
	int temp = m_tick;
	if (m_tick > 0)
		m_tick--;
	if (temp == 1 && m_tick == 0)
		m_function();
}

void Button::draw(sf::RenderWindow*& window, sf::Vector2i mousePos)
{
	if (m_tick == 0) {
		if (mousePos.x >= m_pos.x && mousePos.x <= m_pos.x + m_size.x &&
			mousePos.y >= m_pos.y && mousePos.y <= m_pos.y + m_size.y)
			m_rect.setFillColor(m_hover_c);
		else
			m_rect.setFillColor(m_idle_c);
	}
	window->draw(m_rect);
	window->draw(m_text);
}

void Button::setTick(unsigned tick)
{
	m_ClickTick = tick;
}
