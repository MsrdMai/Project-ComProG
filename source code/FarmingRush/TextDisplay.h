#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
class TextDisplay
{
public:
	sf::Text text;
	int counter = 0;
	bool destroy = false;

	TextDisplay();
	void updatemovement();
	void update(sf::Vector2f movement);

	void update2();
};
