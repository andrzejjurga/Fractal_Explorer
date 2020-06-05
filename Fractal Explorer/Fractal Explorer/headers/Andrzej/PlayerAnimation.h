#pragma once
#include <iostream>
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "World.h"



class PlayerAnimation : public Animation
{
public:
	bool Up = false;
	bool Down = false;
	bool Right = false;
	bool Left = false;
	sf::Texture boom;
	using Animation::Animation;
	void playerAnimationUpdate();
};