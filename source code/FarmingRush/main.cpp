#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Collision.h"
#include "Platform.h"
#include "Inventory.h"
#include "Plant.h"
#include <SFML/Audio.hpp>
#include "TextDisplay.h"
using namespace std;
static const float VIEW_HEIGHT = 864.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view);
void checkCollision(Player* player, sf::Sprite object);
bool inputChecker(sf::Keyboard::Key input);

int Inventory::plantproduct[10] = {};
int Inventory::animalproduct[10] = {};
int Inventory::seed[10] = {};
int Inventory::animalstock[10] = {};

int Inventory::money = 1000;
int Inventory::water = 100;
int Inventory::animalfood = 0;

int slot = NULL;
int mode = 0;
bool facing = false;
bool spade = false;
sf::Sprite facingTo;

int objType = 0;

sf::SoundBuffer buffer;
sf::Sound sound; 
sf::Clock debounce;
sf::Clock timer;



int main() {

	timer.restart();
	sf::RenderWindow window(sf::VideoMode(1536, 864), "Tavernmania Adventure", sf::Style::Resize | sf::Style::Close);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT * 16 / 9, VIEW_HEIGHT ));

	sf::Texture playerTexture;
	playerTexture.loadFromFile("Sofia.png");
	sf::Texture colliderTexture[4];
	colliderTexture[0].loadFromFile("BlackL.png");
	colliderTexture[1].loadFromFile("BlackR.png");
	colliderTexture[2].loadFromFile("BlackT.png");
	colliderTexture[3].loadFromFile("BlackB.png");
	sf::Texture farColliderTexture;
	farColliderTexture.loadFromFile("WhiteC.png");
	sf::Texture platformTexture;
	platformTexture.loadFromFile("FoolDog.png");
	sf::Texture soilTexture;
	soilTexture.loadFromFile("soil.png");
	sf::Texture plantTexture;
	plantTexture.loadFromFile("carrot.png");
	sf::Texture bgTexture;
	bgTexture.loadFromFile("background.png");
	sf::Texture toTexture;
	toTexture.loadFromFile("ThroughOut.png");
	sf::Texture obTexture;
	obTexture.loadFromFile("Obstacle.png");
	sf::Texture DoorTexture;
	DoorTexture.loadFromFile("door.png");
	sf::Texture UITexture;
	UITexture.loadFromFile("UI.png");

	sf::Texture carrotTexture;
	sf::Texture potatoTexture;
	sf::Texture chilliTexture;
	sf::Texture blueberryTexture;
	carrotTexture.loadFromFile("carrot.png");
	potatoTexture.loadFromFile("Potato.png");
	chilliTexture.loadFromFile("Chilli.png");
	blueberryTexture.loadFromFile("Blueberry.png");


	buffer.loadFromFile("Harvest Moon A Wonderful Life SE - Breeze song.wav"); 
	sound.setBuffer(buffer);


	sf::Font font;
	font.loadFromFile("Static-Bold.ttf");
	std::vector<TextDisplay>::const_iterator iter_text;
	std::vector<TextDisplay> textArray;
	TextDisplay text_dm;
	text_dm.text.setFont(font);

	for (int i = 0; i < 10 ; i++)
	{
		Inventory::plantproduct[i]=0;
		Inventory::animalproduct[i] = 0;
		Inventory::seed[i] =0;
		Inventory::animalstock[i] = 0;
	}

	Player player(&playerTexture, colliderTexture, &farColliderTexture, &UITexture, sf::Vector2u(3, 5), 0.3f, 200.0f);
	Plant plant[80];
	for (int i = 0; i < 80; i++) {
		if (i < 10)
		{
			plant[i] = Plant(&soilTexture, 1, sf::Vector2f(-2200, 1300));
			plant[i].setLayout(sf::Vector2f(-2200.0f, 1300.0f - 92.0f * i), sf::Vector2f(1.0f, 1.0f));
		}
		else if (i < 20)
		{
			plant[i] = Plant(&soilTexture, 1, sf::Vector2f(-2000, 1300));
			plant[i].setLayout(sf::Vector2f(-2000.0f, 1300.0f - 92.0f * (i - 10)), sf::Vector2f(1.0f, 1.0f));
		}
		else if (i < 30)
		{
			plant[i] = Plant(&soilTexture, 1, sf::Vector2f(-2200, -600));
			plant[i].setLayout(sf::Vector2f(-2200.0f, -600.0f - 92.0f * (i - 20)), sf::Vector2f(1.0f, 1.0f));
		}
		else if (i < 40)
		{
			plant[i] = Plant(&soilTexture, 1, sf::Vector2f(-2000, -600));
			plant[i].setLayout(sf::Vector2f(-2000.0f, -600.0f - 92.0f * (i - 30)), sf::Vector2f(1.0f, 1.0f));
		}
		else if (i < 50)
		{
			plant[i] = Plant(&soilTexture, 1, sf::Vector2f(-1800, 1300));
			plant[i].setLayout(sf::Vector2f(-1800.0f, 1300.0f - 92.0f * (i - 40)), sf::Vector2f(1.0f, 1.0f));
		}
		else if (i < 60)
		{
			plant[i] = Plant(&soilTexture, 1, sf::Vector2f(-1600, 1300));
			plant[i].setLayout(sf::Vector2f(-1600.0f, 1300.0f - 92.0f * (i - 50)), sf::Vector2f(1.0f, 1.0f));
		}
		else if (i < 70)
		{
			plant[i] = Plant(&soilTexture, 1, sf::Vector2f(-1800, -600));
			plant[i].setLayout(sf::Vector2f(-1800.0f, -600.0f - 92.0f * (i - 60)), sf::Vector2f(1.0f, 1.0f));
		}
		else if (i < 80)
		{
			plant[i] = Plant(&soilTexture, 1, sf::Vector2f(-1600, -600));
			plant[i].setLayout(sf::Vector2f(-1600.0f, -600.0f - 92.0f * (i - 70)), sf::Vector2f(1.0f, 1.0f));
		}

	}
	Platform background(&bgTexture, sf::Vector2f(4.0f, 4.0f), sf::Vector2f(-2560.0f, -2048.0f));
	Platform ThroughOut(&toTexture, sf::Vector2f(4.0f, 4.0f), sf::Vector2f(-2560.0f, -2048.0f));
	Platform Obstacle(&obTexture, sf::Vector2f(4.0f, 4.0f), sf::Vector2f(-2560.0f, -2048.0f));
	Platform Door(&DoorTexture, sf::Vector2f(4.0f, 4.0f), sf::Vector2f(-2560.0f, -2048.0f));

	float deltaTime = 0.0f;
	sf::Clock clock;

	//carrot{type = 0, IMC = 8, growtime = 10, watercapacity = 20, diestate = 7}
	sound.play();
	sound.setLoop(true);
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event action;
		while (window.pollEvent(action)) {
			switch (action.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}

		if (inputChecker(sf::Keyboard::Num1)) mode = 1;
		if (inputChecker(sf::Keyboard::Num2)) mode = 2;
		if (inputChecker(sf::Keyboard::Num3)) mode = 3;
		if (inputChecker(sf::Keyboard::Num4)) mode = 4;


		char face = player.getFace();
		sf::Keyboard::Key faceTo;
		if (face == 'A') faceTo = sf::Keyboard::A;
		else if (face == 'D') faceTo = sf::Keyboard::D;
		else if (face == 'W') faceTo = sf::Keyboard::W;
		else if (face == 'S') faceTo = sf::Keyboard::S;

		for (int i = 0; i < 80; i++)
		{
			checkCollision(&player, plant[i].getSprite());
			if ((player.getFace() == 'L') && (player.checkLeftfar())) facing = true;
			else if ((player.getFace() == 'R') && (player.checkRightfar())) facing = true;
			else if ((player.getFace() == 'T') && (player.checkTopfar())) facing = true;
			else if ((player.getFace() == 'B') && (player.checkBottomfar())) facing = true;
			else facing = false;
			if (facing)
			{
				facingTo = plant[i].getSprite();
				objType = 1;
				slot = i;
				break;
			}
			else objType = 0;
		}

		if (inputChecker(sf::Keyboard::LShift)) {
			switch (mode)
			{
			case 1:
				if (Inventory::money >= 100) {
					Inventory::seed[0] += 1;
					Inventory::money -= 100;
				}
				break;
			case 2:
				if (Inventory::money >= 200) {
					Inventory::seed[1] += 1;
					Inventory::money -= 200;
				}
				break;
			case 3:
				if (Inventory::money >= 400) {
					Inventory::seed[2] += 1;
					Inventory::money -= 400;
				}
				break;
			case 4:
				if (Inventory::money >= 800) {
					Inventory::seed[3] += 1;
					Inventory::money -= 800;
				}
				break;
			default:
				break;
			}
		}

		if (inputChecker(sf::Keyboard::LControl)) {
			switch (mode)
			{
			case 1:
				for (int i = Inventory::plantproduct[0]; i > 0; i--) {
					Inventory::plantproduct[0]--;
					Inventory::money += 200;
				}
				break;
			case 2:
				for (int i = Inventory::plantproduct[1]; i > 0; i--) {
					Inventory::plantproduct[1]--;
					Inventory::money += 400;
				}
				break;
			case 3:
				for (int i = Inventory::plantproduct[2]; i > 0; i--) {
					Inventory::plantproduct[2]--;
					Inventory::money += 800;
				}
				break;
			case 4:
				for (int i = Inventory::plantproduct[3]; i > 0; i--) {
					Inventory::plantproduct[3]--;
					Inventory::money += 1600;
				}
				break;
			default:
				break;
			}
			
		}

		if (inputChecker(sf::Keyboard::Space)) {
			if (objType == 1 && (plant[slot].getState() == 0))
			{
				switch (mode)
				{
				case 1 :
					plant[slot].Planting(0, &carrotTexture, 8, 5, 30, 8, sf::Vector2f(4, 4));
					break;
				case 2 :
					plant[slot].Planting(1, &potatoTexture, 8, 8, 40, 8, sf::Vector2f(4, 4));
					break;
				case 3 :
					plant[slot].Planting(2, &chilliTexture, 10, 15, 50, 10, sf::Vector2f(4, 4));
					break;
				case 4 :
					
					plant[slot].Planting(3, &blueberryTexture, 8, 25, 60, 8, sf::Vector2f(4, 4));
					break;
				default:
					break;
				}
				printf("plant\n");
			}
			else if (objType == 1 && (plant[slot].getState() == plant[slot].diestate - 1))
			{
				switch (plant[slot].type)
				{
				case 0:
					text_dm.text.setString("Carrot +1");
					break;
				case 1:
					text_dm.text.setString("Potato +1");
					break;
				case 2:
					text_dm.text.setString("Chilli +1");
					break;
				case 3:
					text_dm.text.setString("Blueberry +1");
					break;
				default:
					break;
				}
				text_dm.text.setPosition(plant[slot].getSprite().getPosition().x + (plant[slot].getSprite().getLocalBounds().width / 2), plant[slot].getSprite().getPosition().y + (plant[slot].getSprite().getLocalBounds().height / 2));
				textArray.push_back(text_dm);

				plant[slot].Harvest();
				printf("harvest\n");
			}
			else if (objType == 1 && plant[slot].getState() == plant[slot].diestate)
			{
				plant[slot].Reap();
				printf("Reap\n");
			}
			else if (objType == 1 && plant[slot].getState() != plant[slot].diestate)
			{
				plant[slot].Watering();
				printf("Watering\n");
			}
			
		}
		
		if (inputChecker(sf::Keyboard::Numpad5)) printf("%f %f\n", player.getPosition().x, player.getPosition().y);
		
		

		


		checkCollision(&player, Obstacle.getSprite());
		player.Update(deltaTime);
		for (int i = 0; i< 80 ; i++)
		plant[i].Update(deltaTime);

		view.setCenter(player.getPosition());
		window.clear(sf::Color(150, 150, 150));
		window.setView(view);
		background.Draw(window);
		ThroughOut.Draw(window);
		Obstacle.Draw(window);
		Door.Draw(window);
		
		for (int i = 0; i < 80; i++) { plant[i].Draw(window); }
		player.Draw(window);
		int counter = 0;
		for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
		{
			textArray[counter].updatemovement();
			window.draw(textArray[counter].text);
			counter++;
		}

		if (Inventory::money > 10000) break;
		

		window.display();

		

	}

	int a = timer.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		sf::Event action;
		while (window.pollEvent(action)) {
			switch (action.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}

		window.clear(sf::Color(255, 255, 255));

			text_dm.text.setString("Game Clear!");
			text_dm.text.setPosition(player.getPosition());
			text_dm.text.setCharacterSize(100);
			text_dm.text.setOrigin(text_dm.text.getLocalBounds().width / 2, text_dm.text.getLocalBounds().height / 2);
			textArray.push_back(text_dm);
			int counter = 0;
			for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
			{
				textArray[counter].update2();
				window.draw(textArray[counter].text);
				counter++;
			}

			text_dm.text.setString("Score :" + to_string(a) + " seconds");
			text_dm.text.setPosition(player.getPosition().x, player.getPosition().y + 100);
			text_dm.text.setCharacterSize(50);
			text_dm.text.setOrigin(text_dm.text.getLocalBounds().width / 2, text_dm.text.getLocalBounds().height / 2);
			textArray.push_back(text_dm);
			counter = 0;
			for (iter_text = textArray.begin(); iter_text != textArray.end(); iter_text++)
			{
				textArray[counter].update2();
				window.draw(textArray[counter].text);
				counter++;
			}

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

			
			window.display();
	}



		
	return 0;
}



void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void checkCollision(Player* player, sf::Sprite object)
{
	(*player).setCollider
	(
		Collision::PixelPerfectTest((*player).getLeft(), object),
		Collision::PixelPerfectTest((*player).getRight(), object),
		Collision::PixelPerfectTest((*player).getTop(), object),
		Collision::PixelPerfectTest((*player).getBottom(), object),
		Collision::PixelPerfectTest((*player).getSprite(), object),
		Collision::PixelPerfectTest((*player).getLeftfar(), object),
		Collision::PixelPerfectTest((*player).getRightfar(), object),
		Collision::PixelPerfectTest((*player).getTopfar(), object),
		Collision::PixelPerfectTest((*player).getBottomfar(), object)
	);
}

bool inputChecker(sf::Keyboard::Key input)
{

	if (sf::Keyboard::isKeyPressed(input) && debounce.getElapsedTime().asSeconds() > 0.3f) {
		debounce.restart();
		return true;
	}
	else return false;
	
}
