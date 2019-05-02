#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "TextDisplay.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::Texture* colliderTexture,sf::Texture* farColliderTexture, sf::Texture* UITexture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();


	void setCollider(bool lc, bool rc, bool tc, bool bc, bool pc, bool lfc, bool rfc, bool tfc, bool bfc);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	

	sf::Vector2f getPosition() { return body.getPosition(); }
	sf::Sprite getSprite() { return body; }
	sf::Sprite getLeft() { return left; }
	sf::Sprite getRight() { return right; }
	sf::Sprite getTop() { return top; }
	sf::Sprite getBottom() { return bottom; }
	sf::Sprite getLeftfar() { return leftfar; }
	sf::Sprite getRightfar() { return rightfar; }
	sf::Sprite getTopfar() { return topfar; }
	sf::Sprite getBottomfar() { return bottomfar; }
	bool checkLeft() { return lc; }
	bool checkRight() { return rc; }
	bool checkTop() { return tc; }
	bool checkBottom() { return bc; }
	bool checkLeftfar() { return lfc; }
	bool checkRightfar() { return rfc; }
	bool checkTopfar() { return tfc; }
	bool checkBottomfar() { return bfc; }
	char getFace() { return faceTo; }
	
	


private:
	bool rc = false, lc = false, tc = false, bc = false, pc = false;
	bool rfc = false, lfc = false, tfc = false, bfc = false, pfc = false;
	sf::Sprite body;
	sf::Sprite left, right, top, bottom;
	sf::Sprite leftfar, rightfar, topfar, bottomfar;
	sf::Sprite UI;
	sf::Text text;
	sf::Font font;
	TextDisplay text_dm;
	std::vector<TextDisplay>::const_iterator iter_text;
	std::vector<TextDisplay> textArray;
	Animation animation;
	unsigned int row;
	float speed;
	char faceTo;
};

