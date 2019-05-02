#include "Player.h"
#include "Collision.h"
#include "TextDisplay.h"
#include "Inventory.h"

Player::Player(sf::Texture* texture, sf::Texture* colliderTexture, sf::Texture* farColliderTexture, sf::Texture* UITexture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;

	this->lc = false;
	this->rc = false;
	this->tc = false;
	this->bc = false;
	this->pc = false;

	body.setTexture(*texture);
	body.setPosition(-700.0f, -150.0f);
	//body.setOrigin(body.getLocalBounds().width / imageCount.x / 2.0f, body.getLocalBounds().height / imageCount.y / 2.0f);
	body.setScale(sf::Vector2f(2.0f,2.0f));

	printf("%f %f\n", body.getLocalBounds().width, body.getLocalBounds().height);

	left.setTexture(colliderTexture[0]);
	left.setPosition(body.getPosition().x - body.getLocalBounds().width / imageCount.x * body.getScale().x, body.getPosition().y);
	//left.setOrigin(left.getLocalBounds().width/2, left.getLocalBounds().height/2);
	left.setScale(sf::Vector2f(2.0f,2.0f));

	right.setTexture(colliderTexture[1]);
	right.setPosition(body.getPosition().x + body.getLocalBounds().width / imageCount.x * body.getScale().x, body.getPosition().y);
	//right.setOrigin(right.getLocalBounds().width/2, right.getLocalBounds().height/2);
	right.setScale(sf::Vector2f(2.0f,2.0f));

	top.setTexture(colliderTexture[2]);
	top.setPosition(body.getPosition().x, body.getPosition().y - body.getLocalBounds().height / imageCount.y * body.getScale().y);
	//top.setOrigin(top.getLocalBounds().width/2, top.getLocalBounds().height/2);
	top.setScale(sf::Vector2f(2.0f,2.0f));

	bottom.setTexture(colliderTexture[3]);
	bottom.setPosition(body.getPosition().x, body.getPosition().y + body.getLocalBounds().height / imageCount.y * body.getScale().y);
	//bottom.setOrigin(bottom.getLocalBounds().width/2, bottom.getLocalBounds().height/2);
	bottom.setScale(sf::Vector2f(2.0f,2.0f));

	leftfar.setTexture(*farColliderTexture);
	leftfar.setPosition(body.getPosition().x - body.getLocalBounds().width / imageCount.x * body.getScale().x, body.getPosition().y);
	//leftfar.setOrigin(leftfar.getLocalBounds().width/2, leftfar.getLocalBounds().height/2);
	leftfar.setScale(sf::Vector2f(2.0f,2.0f));

	rightfar.setTexture(*farColliderTexture);
	rightfar.setPosition(body.getPosition().x + body.getLocalBounds().width / imageCount.x * body.getScale().x, body.getPosition().y);
	//rightfar.setOrigin(rightfar.getLocalBounds().width/2, rightfar.getLocalBounds().height/2);
	rightfar.setScale(sf::Vector2f(2.0f,2.0f));

	topfar.setTexture(*farColliderTexture);
	topfar.setPosition(body.getPosition().x, body.getPosition().y - body.getLocalBounds().height / imageCount.y * body.getScale().y);
	//topfar.setOrigin(topfar.getLocalBounds().width/2, topfar.getLocalBounds().height/2);
	topfar.setScale(sf::Vector2f(2.0f,2.0f));

	bottomfar.setTexture(*farColliderTexture);
	bottomfar.setPosition(body.getPosition().x, body.getPosition().y + body.getLocalBounds().height / imageCount.y * body.getScale().y);
	//bottomfar.setOrigin(bottomfar.getLocalBounds().width/2, bottomfar.getLocalBounds().height/2);
	bottomfar.setScale(sf::Vector2f(2.0f,2.0f));

	
	UI.setTexture(*UITexture);
	UI.setPosition(body.getPosition().x, body.getPosition().y);
	UI.setOrigin(UI.getLocalBounds().width / 2, UI.getLocalBounds().height / 2);

	
	font.loadFromFile("Static-Bold.ttf");
	text_dm.text.setFont(font);
}


Player::~Player()
{
}

void Player::setCollider(bool lc, bool rc, bool tc, bool bc, bool pc, bool lfc, bool rfc, bool tfc, bool bfc)
{
	this->lc = lc; 
	this->rc = rc;
	this->tc = tc;
	this->bc = bc;
	this->pc = pc;
	this->lfc = lfc;
	this->rfc = rfc;
	this->tfc = tfc;
	this->bfc = bfc;
}


void Player::Update(float deltaTime)
{
	
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !lc)
	{
		movement.x -= speed * deltaTime;
		faceTo = 'L';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !rc)
	{
		movement.x += speed * deltaTime;
		faceTo = 'R';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !tc)
	{
		movement.y -= speed * deltaTime;
		faceTo = 'T';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !bc)
	{
		movement.y += speed * deltaTime;
		faceTo = 'B';
	}

	if (movement.x == 0.0f && movement.y == 0.0f)
	{
		row = 4;
	}
	else if (movement.y == 0.0f)
	{
		if (movement.x > 0.0f) {
			row = 2;
		}
		else {
			row = 1;
		}
	}
	else if (movement.x == 0.0f)
	{
		if (movement.y > 0.0f) {
			row = 0;
		}
		else {
			row = 3;
		}
	}
	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);

	
	left.move(movement);
	right.move(movement);
	top.move(movement);
	bottom.move(movement);
	leftfar.move(movement);
	rightfar.move(movement);
	topfar.move(movement);
	bottomfar.move(movement);
	body.move(movement);
	UI.move(movement);
	text_dm.update(movement);
}
void Player::Draw(sf::RenderWindow& window)
{
	window.draw(left);
	window.draw(right);
	window.draw(top);
	window.draw(bottom);
	window.draw(leftfar);
	window.draw(rightfar);
	window.draw(topfar);
	window.draw(bottomfar);
	window.draw(body);
	window.draw(UI);

	text_dm.text.setString(to_string(Inventory::seed[0]));
	text_dm.text.setPosition(body.getPosition().x - 600, body.getPosition().y - 280);
	textArray.push_back(text_dm);
	int i = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{

		if (textArray[i].destroy == true)
		{
			textArray.erase(iter_text);
			break;
		}
		i++;
	}
	int counter = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{
		textArray[counter].updatemovement();
		window.draw(textArray[counter].text);
		counter++;
	}


	text_dm.text.setString(to_string(Inventory::seed[1]));
	text_dm.text.setPosition(body.getPosition().x - 600, body.getPosition().y - 160);
	textArray.push_back(text_dm);
	i = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{

		if (textArray[i].destroy == true)
		{
			textArray.erase(iter_text);
			break;
		}
		i++;
	}
	counter = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{
		textArray[counter].updatemovement();
		window.draw(textArray[counter].text);
		counter++;
	}

	text_dm.text.setString(to_string(Inventory::seed[2]));
	text_dm.text.setPosition(body.getPosition().x - 600, body.getPosition().y - 40);
	textArray.push_back(text_dm);
	i = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{

		if (textArray[i].destroy == true)
		{
			textArray.erase(iter_text);
			break;
		}
		i++;
	}
	counter = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{
		textArray[counter].updatemovement();
		window.draw(textArray[counter].text);
		counter++;
	}

	text_dm.text.setString(to_string(Inventory::seed[3]));
	text_dm.text.setPosition(body.getPosition().x - 600, body.getPosition().y + 80);
	textArray.push_back(text_dm);
	i = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{

		if (textArray[i].destroy == true)
		{
			textArray.erase(iter_text);
			break;
		}
		i++;
	}
	counter = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{
		textArray[counter].updatemovement();
		window.draw(textArray[counter].text);
		counter++;
	}

	text_dm.text.setString(to_string(Inventory::plantproduct[0]));
	text_dm.text.setPosition(body.getPosition().x + 580, body.getPosition().y - 280);
	textArray.push_back(text_dm);
	i = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{

		if (textArray[i].destroy == true)
		{
			textArray.erase(iter_text);
			break;
		}
		i++;
	}
	counter = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{
		textArray[counter].updatemovement();
		window.draw(textArray[counter].text);
		counter++;
	}

	text_dm.text.setString(to_string(Inventory::plantproduct[1]));
	text_dm.text.setPosition(body.getPosition().x + 580, body.getPosition().y - 160);
	textArray.push_back(text_dm);
	i = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{

		if (textArray[i].destroy == true)
		{
			textArray.erase(iter_text);
			break;
		}
		i++;
	}
	counter = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{
		textArray[counter].updatemovement();
		window.draw(textArray[counter].text);
		counter++;
	}


	text_dm.text.setString(to_string(Inventory::plantproduct[2]));
	text_dm.text.setPosition(body.getPosition().x + 580, body.getPosition().y - 40);
	textArray.push_back(text_dm);
	i = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{

		if (textArray[i].destroy == true)
		{
			textArray.erase(iter_text);
			break;
		}
		i++;
	}
	counter = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{
		textArray[counter].updatemovement();
		window.draw(textArray[counter].text);
		counter++;
	}


	text_dm.text.setString(to_string(Inventory::plantproduct[3]));
	text_dm.text.setPosition(body.getPosition().x + 580, body.getPosition().y + 80);
	textArray.push_back(text_dm);
	i = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{

		if (textArray[i].destroy == true)
		{
			textArray.erase(iter_text);
			break;
		}
		i++;
	}
	counter = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{
		textArray[counter].updatemovement();
		window.draw(textArray[counter].text);
		counter++;
	}

	text_dm.text.setString(to_string(Inventory::water));
	text_dm.text.setPosition(body.getPosition().x + -600, body.getPosition().y + 350);
	textArray.push_back(text_dm);
	i = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{

		if (textArray[i].destroy == true)
		{
			textArray.erase(iter_text);
			break;
		}
		i++;
	}
	counter = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{
		textArray[counter].updatemovement();
		window.draw(textArray[counter].text);
		counter++;
	}

	text_dm.text.setString(to_string(Inventory::money));
	text_dm.text.setPosition(body.getPosition().x + +520, body.getPosition().y + 350);
	textArray.push_back(text_dm);
	i = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{

		if (textArray[i].destroy == true)
		{
			textArray.erase(iter_text);
			break;
		}
		i++;
	}
	counter = 0;
	for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
	{
		textArray[counter].updatemovement();
		window.draw(textArray[counter].text);
		counter++;
	}
}



