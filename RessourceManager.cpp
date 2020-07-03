#include "RessourceManager.h"
#include <iostream>

void RessourceManager::add(const std::string& source, const sf::Texture& texture)
{
	std::cout << "Added " << source << "\n";
	texturePair.push_back(std::make_pair(source, texture));
}
