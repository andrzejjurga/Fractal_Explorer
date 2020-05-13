#pragma once
#include <iostream>
#include <Box2d/Box2D.h>
#include "Animation.h"
#include "PlayerAnimation.h"
#include "World.h"

using namespace std;

class Player
{
public:
	b2BodyDef bodyDef;
	b2Body* body;
	//b2PolygonShape dynamicBox;
	b2PolygonShape shipShape;
	b2Vec2 vartices[8];
	b2FixtureDef fixtureDef;
	b2Vec2 position;
	float32 angle;
	b2Vec2 currentRightNormal;
	b2Vec2 impulse;
	b2Vec2 currentForwardNormal;
	b2Vec2 currentForwardSpeed;
	float currentSpeed;
	float maxLateralImpulse = 2.5f;
	bool Up = false;
	bool Down = false;
	bool Right = false;
	bool Left = false;
	//konstruktor
	Player(World * swiat, float X, float Y);

	void playerUpdate(PlayerAnimation* animation);

	b2Vec2 getLateralValocity();
	b2Vec2 getForwardVelocity();
	void updateFriction();
	b2Vec2 getPosition();
};
