#pragma once
#include <SFML/Graphics.hpp>
class State
{
public:
	State();
	State(sf::Texture* texture, int imageCount);
	State(sf::Texture* texture, int imageCount,int dieState);
	~State();

	void nextState();
	void setState(int state);
	void setStateMachine(sf::Texture* texture, int imageCount, int dieState);

	int getState() { return currentImage; }
	int getDieState() { return dieState; }

public:
	sf::IntRect uvRect;

private:
	int imageCount;
	int currentImage;
	int dieState;
};

