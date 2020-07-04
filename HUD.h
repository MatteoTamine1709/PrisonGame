#pragma once
#include <vector>
#include "Button.h"
class HUD
{
private:
	std::vector<Button *> buttons;
	int tick = 0;
	int clickTick = 15;
public:
	bool onClick(sf::Vector2i mousePos);
	void update(void);
	void draw(sf::RenderWindow*& window, sf::Vector2i mousePos);
	void push_button(Button& button);
};

