#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include "Animation.h"
#include "PlayerAnimation.h"
#include "World.h"
#include "Collision.h"


using namespace std;

class Player
{
public:
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shipShape;
	b2Vec2 vartices[8];
	b2FixtureDef fixtureDef;
	b2Vec2 position;
	float angle;
	b2Vec2 currentRightNormal;
	b2Vec2 impulse;
	b2Vec2 currentForwardNormal;
	b2Vec2 currentForwardSpeed;
	float currentSpeed;
	float maxLateralImpulse;
	float enginePower;
	bool Up = false;
	bool Down = false;
	bool Right = false;
	bool Left = false;
	bool connect = false;

	int HP; //Punkty ¿ycia statku
	//konstruktor
	Player(World * swiat, float X, float Y);

	void playerUpdate(PlayerAnimation* animation);

	b2Vec2 getLateralValocity();
	b2Vec2 getForwardVelocity();
	void updateFriction();
	b2Vec2 getPosition();
	
	void hitDamage(PlayerAnimation* animation);
	void startContact();
};
