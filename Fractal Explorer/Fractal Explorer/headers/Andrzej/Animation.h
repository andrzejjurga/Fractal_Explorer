#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Animation
{
public:
	sf::Clock clock;
	sf::Texture texture;
	string file;
	float height;
	float width;
	int amount;
	float speed;
	sf::IntRect rectSourceSprite;
	sf::Sprite sprite;

	Animation();
	Animation(string _file, float _height, float _width, int _amount, float _speed);

	void AnimationUpdate(sf::Vector2f position = {0.f,0.f});
	Animation& operator=(const Animation& obj);
};
