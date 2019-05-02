#pragma once
#include <SFML\Graphics.hpp>
#include "State.h"
#include "Inventory.h"
class Plant
{
public:
	Plant();

	Plant(sf::Texture * texture, int imageCount, sf::Vector2f position);
	~Plant();

	void setLayout(sf::Vector2f position, sf::Vector2f scale);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Planting(int type, sf::Texture * texture, int imageCount, float growtime, float dietime, int dieState, sf::Vector2f scale);
	void Watering();
	void Harvest();
	void Reap();
	void Fertilizing();
	int getState() { return state; }
	sf::Sprite getSprite() { return body; };


public:
	int type;
	int state;
	int diestate;
	int imageCount;
	float growtime;
	float dietime;
	State stateMachine;
	sf::Sprite body;
	sf::Vector2f position;
	sf::Clock water;
	sf::Clock lifetime;
	sf::Sprite soil;
};

