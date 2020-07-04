#include "RessourceManager.h"
#include "Log.h"
#include <iostream>

RessourceManager::RessourceManager()
{
	m_defaultTexture = new sf::Texture();
	if (!m_defaultTexture->loadFromFile("defaultTexture.jpg")) {
		LOG.Error("Could not load default texture. EXIT");
		exit(EXIT_FAILURE);
	}
}

RessourceManager::~RessourceManager()
{
	sf::Sprite sprite;
	for (int i = 0; i < texturePair.size(); i++) {
		delete (texturePair[i].second);
		LOG.Info("Deleted Texture : " + texturePair[i].first);
	}
}

void RessourceManager::add(const std::string& source, sf::Texture* &texture)
{
	LOG.Info("Created new Texture : " + source);
	texturePair.push_back(std::make_pair(source, texture));
}

sf::Texture* RessourceManager::getTexture(const std::string& source)
{
	int i = 0;

	for (i = 0; i < texturePair.size(); i++) {
		if (texturePair[i].first.compare(source) == 0) {
			LOG.Info("Using Texture : " + source);
			return (texturePair[i].second);
		}
	}
	if (i == texturePair.size()) {
		sf::Texture *texture = new sf::Texture();
		if (!texture->loadFromFile(source)) {
			LOG.Warn("Could not load " + source + " texture. Loading default texture");
			return (m_defaultTexture);
		}
		add(source, texture);
		return (getTexture(source));
	}
}
