#include "FPSCounter.h"
#include "Log.h"

FPSCounter::FPSCounter()
{
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile("arial.ttf")) {
		LOG.Warn("Could not load arial.ttf font. Loading default font");
		delete (font);
	}
	else {
		text.setFont(*font);
	}
	text.setPosition(20, 20);
	text.setCharacterSize(20);
}

FPSCounter::~FPSCounter()
{
	delete (text.getFont());
}

float FPSCounter::display(sf::RenderWindow*& window)
{
	compute();
	text.setString(std::to_string(FPSCount));
	window->draw(text);
	return (FPSCount);
}

void FPSCounter::compute(void)
{
	sf::Time t = clock.restart();
	float sec = t.asSeconds();
	FPSCount = 1.0f / sec;
}
