#pragma once
#include <iostream>
#include <Box2d/Box2D.h>
#include "Animation.h"
#include "World.h"
#include "Player.h"

using namespace std;

class Enemy
{
public:
	b2BodyDef bodyDef;
	b2PolygonShape shipShape;
	b2Vec2 vartices[8];
	b2Body* body;
	b2FixtureDef fixtureDef;
	b2Vec2 position;
	float32 angle;

	b2Vec2 currentRightNormal;
	b2Vec2 impulse;
	b2Vec2 currentForwardNormal;
	b2Vec2 currentForwardSpeed;
	float currentSpeed;
	float maxLateralImpulse = 2.5f;
	//namierzanie gracza
	b2Vec2 pleyerPosition; //pozycja gracza
	float playerAngle; //kont na lini którego le¿y gracz
	float totalRotation; //ca³y kont potrzebny do ustawienia siê przodem do gracza
	float calAngle; //kont wyliczny z wyprzedzeniem dla torqa
	float torque;
	//konstruktor
	Enemy(World* swiat, float X, float Y);

	void enemyUpdate(Animation* animation, Player* gracz);

	b2Vec2 getLateralValocity();
	b2Vec2 getForwardVelocity();
	void updateFriction();
};
