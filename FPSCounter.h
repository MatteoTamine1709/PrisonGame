#pragma once
#include <SFML/Graphics.hpp>

class FPSCounter
{
private:
	sf::Text text;
	float FPSCount = 0;
	sf::Clock clock;
	void compute(void);

public:
	FPSCounter();
	~FPSCounter();
	float display(sf::RenderWindow*& window);
};