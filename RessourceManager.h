#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class RessourceManager
{
private:
	sf::Texture* m_defaultTexture;
public:
	RessourceManager();
	~RessourceManager();
	std::vector<std::pair<std::string, sf::Texture* >> texturePair;

	virtual void add(const std::string& source, sf::Texture* &texture);
	virtual sf::Texture* getTexture(const std::string& source);
};