#include "State.h"



State::State()
{
}

State::State(sf::Texture * texture, int imageCount)
{
	this->imageCount = imageCount;
	this->dieState = NULL;
	currentImage = 0;
	uvRect.top = 0;
	uvRect.width = texture->getSize().x / float(imageCount);
	uvRect.height = texture->getSize().y;
}

State::State(sf::Texture* texture, int imageCount,int dieState)
{
	this->imageCount = imageCount;
	this->dieState = dieState;
	currentImage = 0;
	uvRect.top = 0;
	uvRect.width = texture->getSize().x / float(imageCount);
	uvRect.height = texture->getSize().y;
}


State::~State()
{
}

void State::nextState()
{
	currentImage++;
	uvRect.left = currentImage * abs(uvRect.width);
	uvRect.width = abs(uvRect.width);
}

void State::setState(int state)
{
	currentImage = state;
	uvRect.left = currentImage * abs(uvRect.width);
	uvRect.width = abs(uvRect.width);
}

void State::setStateMachine(sf::Texture * texture, int imageCount, int dieState)
{
	this->imageCount = imageCount;
	this->dieState = dieState;
	currentImage = 0;
	uvRect.top = 0;
	uvRect.width = texture->getSize().x / float(imageCount);
	uvRect.height = texture->getSize().y;
}
