#pragma once
#include "SFML/Graphics.hpp"
#include "RessourceManager.h"
#include <vector>

class Animation
{
private:
	sf::Sprite m_sprite;
	sf::Texture* m_texture;
	int m_rectIndex = 0;
	std::vector<sf::IntRect> m_textureRects;
	int m_tickUpdate = 30;
	int m_tickCounter = 0;

public:
	RessourceManager *ressourceManager;

	void setTexture(const std::string& str);
	Animation(const std::string source, std::vector<sf::IntRect> &textureRects, RessourceManager &manager);
	Animation(std::string source, RessourceManager& manager);
	~Animation();

	void setTickUpdate(int tick);
	void draw(sf::RenderWindow* &window);
	void update(void);
	void setPosition(const sf::Vector2f &pos);
};

