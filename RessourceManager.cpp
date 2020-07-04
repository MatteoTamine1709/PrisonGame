#include "RessourceManager.h"
#include <iostream>

RessourceManager::~RessourceManager()
{
	for (int i = 0; i < texturePair.size(); i++) {
		std::cout << "Deleted Texture : " << texturePair[i].first << "\n";
		delete (texturePair[i].second);
	}
}

void RessourceManager::add(const std::string& source, sf::Texture* texture)
{
	std::cout << "Created new Texture : " << source << "\n";
	texturePair.push_back(std::make_pair(source, texture));
}
