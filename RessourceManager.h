#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "AI.h"

class RessourceManager
{
private:
	sf::Texture* m_defaultTexture;
	sf::Font* m_defaultFont;
	std::vector<std::pair<std::string, sf::Texture* >> texturePair;
	std::vector<std::pair<std::string, sf::Font* >> fontPair;
	std::deque<AI*> aiQueue;
public:
	RessourceManager();
	~RessourceManager();

	virtual void add(const std::string& source, sf::Texture*& texture);
	virtual void add(const std::string& source, sf::Font*& font);
	virtual sf::Texture* getTexture(const std::string& source);
	virtual sf::Font* getFont(const std::string& source);
	virtual void push_ai(AI*& ai);
	virtual void processAI(void);
};