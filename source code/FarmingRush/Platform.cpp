#include "Platform.h"


Platform::Platform(sf::Texture * texture, sf::Vector2f scale, sf::Vector2f position) 
{
	body.setTexture(*texture);

	body.setPosition(position);
	body.setScale(scale);
}

Platform::~Platform()
{
}

void Platform::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Update()
{
	
}