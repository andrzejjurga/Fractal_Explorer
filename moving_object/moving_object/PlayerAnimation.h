#pragma once
#include <iostream>
#include "Animation.h"
#include "World.h"



class PlayerAnimation : public Animation
{
public:
	bool Up = false;
	bool Down = false;
	bool Right = false;
	bool Left = false;
	using Animation::Animation;
	void playerAnimationUpdate();
};