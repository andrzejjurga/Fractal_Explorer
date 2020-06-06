#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include "Player.h"
#include "World.h"

class Explosion
{
	sf::Texture texture;
	sf::IntRect rectSourceSprite;
	string file;
	float height;
	float width;
public:
	int amount;
	sf::Sprite sprite;

	Explosion();
	void update();
};
