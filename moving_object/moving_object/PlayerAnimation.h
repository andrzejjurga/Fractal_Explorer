#pragma once
#include <iostream>
#include "Animation.h"

class PlayerAnimation : public Animation
{
public:
	using Animation::Animation;
	bool Up = false;
	bool Down = false;
	bool Right = false;
	bool Left = false;

	void playerAnimationUpdate();
};