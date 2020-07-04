#include "HUD.h"

bool HUD::onClick(sf::Vector2i mousePos)
{
	for (int i = 0; i < buttons.size(); i++)
		if (buttons[i]->onClick(mousePos))
			return true;
	return false;
}

void HUD::update(void)
{
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->update();
}

void HUD::draw(sf::RenderWindow*& window, sf::Vector2i mousePos)
{
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->draw(window, mousePos);
}

void HUD::push_button(Button& button)
{
	buttons.push_back(&button);
}
