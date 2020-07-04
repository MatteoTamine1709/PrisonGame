#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class RessourceManager
{
private:
	sf::Texture* m_defaultTexture;
	sf::Font* m_defaultFont;
public:
	RessourceManager();
	~RessourceManager();
	std::vector<std::pair<std::string, sf::Texture* >> texturePair;
	std::vector<std::pair<std::string, sf::Font* >> fontPair;

	virtual void add(const std::string& source, sf::Texture*& texture);
	virtual void add(const std::string& source, sf::Font*& font);
	virtual sf::Texture* getTexture(const std::string& source);
	virtual sf::Font* getFont(const std::string& source);
};