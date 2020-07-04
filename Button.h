#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "RessourceManager.h"

class Button
{
private:
	sf::Vector2i m_pos;
	sf::Vector2f m_size;
	const std::string m_name;
	int (*m_function)(void);
	sf::RectangleShape m_rect;
	int m_tick = 0;
	int m_ClickTick = 15;
	sf::Text m_text;

public:
	sf::Color m_idle_c = sf::Color::Blue;
	sf::Color m_hover_c = sf::Color::Black;
	sf::Color m_clicked_c = sf::Color::Red;
public:
	RessourceManager* ressourceManager;
	Button(RessourceManager &manager, sf::Vector2i pos, sf::Vector2f size, const std::string& name, const sf::Color &color = sf::Color::White);
	Button(RessourceManager& manager, sf::Vector2i pos, sf::Vector2f size, const std::string& name, const std::string& texturepath, const sf::Color& color = sf::Color::White);
	~Button(void);
	bool onClick(sf::Vector2i mousePos);
	void update(void);
	void draw(sf::RenderWindow *&window, sf::Vector2i mousePos);
	void setTick(unsigned tick);
};

