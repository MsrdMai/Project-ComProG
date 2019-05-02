#pragma once
#include <SFML/Graphics.hpp>
class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f scale, sf::Vector2f position);
	~Platform();

	void Draw(sf::RenderWindow& window);
	

	sf::Sprite getSprite() { return body; }

private:
	sf::Sprite body;
};

