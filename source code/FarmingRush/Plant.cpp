#include "Plant.h"
#include "Inventory.h"
#include <iostream>


Plant::Plant() {
	state = 0;
}

Plant::Plant(sf::Texture * texture, int imageCount, sf::Vector2f position) :
	stateMachine(texture,1)
{
	state = 0;
	soil.setTexture(*texture);
	soil.setPosition(position);
	
	body.setTexture(*texture);

	body.setPosition(position);
	
	this->position = position;
	this->imageCount = imageCount;


}

Plant::~Plant()
{
}

void Plant::setLayout(sf::Vector2f position,sf::Vector2f scale)
{
	soil.setPosition(position);

	soil.setScale(scale);
	body.setPosition(position);
	
	body.setScale(scale);
	this->position = position;
}

void Plant::Update(float deltaTime)
{
	if (state != stateMachine.getDieState() && state != 0) {
		if (((lifetime.getElapsedTime().asSeconds()) >= growtime))
		{
			if (state < stateMachine.getDieState()-1)
			state += 1;
			&lifetime.restart();
		}

		if ((water.getElapsedTime().asSeconds() >= dietime && state != stateMachine.getDieState()-1))
		{
			state = stateMachine.getDieState();
		}

	}
	if (state != 0)stateMachine.setState(state-1);
	body.setTextureRect(stateMachine.uvRect);
}

void Plant::Planting(int type, sf::Texture * texture, int imageCount, float growtime, float dietime, int dieState,sf::Vector2f scale)
{
	if (Inventory::seed[type] > 0) {
		stateMachine.setStateMachine(texture, imageCount, dieState);
		body.setTexture(*texture);
		body.setPosition(position.x + 20.0f, position.y);
		body.setScale(scale);

		this->diestate = dieState;


		state = 1;
		this->type = type;
		this->growtime = growtime;
		this->dietime = dietime;
		Inventory::seed[type] -= 1;
		lifetime.restart();
		water.restart();
	}
}

void Plant::Watering()
{
	water.restart();
	Inventory::water -= 1;
}

void Plant::Harvest()
{
	state = 0;
	Inventory::plantproduct[type] += 1;
}

void Plant::Reap()
{
	state = 0;
}

void Plant::Fertilizing()
{
	growtime -= (growtime / 4.0f);
}

void Plant::Draw(sf::RenderWindow& window)
{
	window.draw(soil);
	if (state != 0)	window.draw(body);
}