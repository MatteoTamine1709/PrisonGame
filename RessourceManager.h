#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class RessourceManager
{
public:
	std::vector<std::pair<std::string, sf::Texture>> texturePair;

	virtual void add(const std::string& source, const sf::Texture& texture);
};

