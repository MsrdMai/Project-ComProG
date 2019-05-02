#include "TextDisplay.h"
#include <SFML/Graphics.hpp>
TextDisplay::TextDisplay()
{
	text.setFillColor(sf::Color::Black);  
	text.setCharacterSize(40);    
	text.setPosition(0, 0);
}
void TextDisplay::updatemovement()
{
	text.move(0, -1);              
	counter++;
	if (counter >= 100)              
	{
		destroy = true;              
	}
}

void TextDisplay::update(sf::Vector2f movement) {
	text.move(movement);
	counter++;
	if (counter >= 2)
	{
		destroy = true;
	}
}

void TextDisplay::update2()
{
	counter++;
	if (counter >= 1)
	{
		destroy = true;
	}
}
