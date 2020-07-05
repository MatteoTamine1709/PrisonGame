#include "RessourceManager.h"
#include "Log.h"
#include <iostream>

RessourceManager::RessourceManager()
{
	//aiQueue = new (std::deque<AI*>);
	m_defaultTexture = new sf::Texture();
	if (!m_defaultTexture->loadFromFile("defaultTexture.jpg")) {
		LOG.Error("Could not load default texture. EXIT");
		exit(EXIT_FAILURE);
	}
	m_defaultFont = new sf::Font();
	if (!m_defaultFont->loadFromFile("arial.ttf")) {
		LOG.Error("Could not load default font. EXIT");
		exit(EXIT_FAILURE);
	}
}

RessourceManager::~RessourceManager()
{
	for (int i = 0; i < texturePair.size(); i++) {
		delete (texturePair[i].second);
		LOG.Info("Deleted Texture : " + texturePair[i].first);
	}
	delete (m_defaultTexture);
	for (int i = 0; i < fontPair.size(); i++) {
		delete (fontPair[i].second);
		LOG.Info("Deleted Font : " + fontPair[i].first);
	}
	delete (m_defaultFont);
}

void RessourceManager::add(const std::string& source, sf::Texture* &texture)
{
	LOG.Info("Created new Texture : " + source);
	texturePair.push_back(std::make_pair(source, texture));
}

void RessourceManager::add(const std::string& source, sf::Font*& font)
{
	LOG.Info("Created new Font : " + source);
	fontPair.push_back(std::make_pair(source, font));
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
			delete (texture);
			return (m_defaultTexture);
		}
		add(source, texture);
		return (getTexture(source));
	}
}

sf::Font* RessourceManager::getFont(const std::string& source)
{
	int i = 0;

	for (i = 0; i < fontPair.size(); i++) {
		if (fontPair[i].first.compare(source) == 0) {
			LOG.Info("Using Texture : " + source);
			return (fontPair[i].second);
		}
	}
	if (i == fontPair.size()) {
		sf::Font* font = new sf::Font();
		if (!font->loadFromFile(source)) {
			LOG.Warn("Could not load " + source + " font. Loading default font");
			delete (font);
			return (m_defaultFont);
		}
		add(source, font);
		return (getFont(source));
	}
}

void RessourceManager::push_ai(AI*& ai)
{
	if (aiQueue.size() < 1000)
		aiQueue.push_back(ai);
}

void RessourceManager::processAI(void)
{
	AI *ai;
	bool update = false;
	for (int i = 0; i < 50 && aiQueue.size() > 0; i++) {
		ai = aiQueue.front();
		ai->getPath();
		aiQueue.pop_front();
		update = true;
	}
	if (update)
		LOG.Info("AI left to process : " + std::to_string(aiQueue.size()));
}
