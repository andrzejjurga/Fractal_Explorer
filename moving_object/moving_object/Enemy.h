#pragma once
#include <iostream>
#include <Box2d/Box2D.h>
#include "Animation.h"
#include "World.h"

using namespace std;

class Enemy
{
public:
	b2BodyDef bodyDef;
	b2PolygonShape dynamicBox;
	b2Body* body;
	b2FixtureDef fixtureDef;
	b2Vec2 position;
	float32 angle;
	//konstruktor
	Enemy(World* swiat, float X, float Y);

	void enemyUpdate(Animation* animation);

};
