#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ParticuleEngine.h"
#include "FPSCounter.h"
#include "AI.h"

class RessourceManager
{
private:
	sf::Texture* m_defaultTexture;
	sf::Font* m_defaultFont;
	std::vector<std::pair<std::string, sf::Texture* >> texturePair;
	std::vector<std::pair<std::string, sf::Font* >> fontPair;
	std::deque<AI*> aiQueue;
	FPSCounter fps;

	void copyTextureFromManager(RessourceManager& manager);
	void copyFontFromManager(RessourceManager& manager);
	void copyAIFromManager(RessourceManager& manager);
public:
	RessourceManager();
	~RessourceManager();

	ParticuleEngine particuleEngine;
	virtual void add(const std::string& source, sf::Texture*& texture);
	virtual void add(const std::string& source, sf::Font*& font);
	virtual sf::Texture* getTexture(const std::string& source);
	virtual sf::Font* getFont(const std::string& source);
	virtual void push_ai(AI*& ai);
	virtual void processAI(void);
	virtual float getFPS(sf::RenderWindow *&window);
	virtual void copyRessourceManager(RessourceManager& manager);
};