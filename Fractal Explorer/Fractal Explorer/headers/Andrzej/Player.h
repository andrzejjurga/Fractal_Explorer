#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include "Animation.h"
#include "PlayerAnimation.h"
#include "World.h"
#include <FractalCollision.h>
#include <MandelViewer.h>
#include <cmath>


using namespace std;

class Player
{
public:
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shipShape;
	b2Vec2 vertices[8];
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
	FractalCollision fractalCollision;//kolizje 
	int HP; //Punkty ¿ycia statku
	sf::RectangleShape HPSprite;
	sf::RectangleShape HPSpriteOutline;
	//konstruktor
	Player(World* swiat, PlayerAnimation* animation, FractalRenderer* map, float X, float Y);

	void playerUpdate(PlayerAnimation* animation, FractalRenderer* map);

	b2Vec2 getLateralValocity();
	b2Vec2 getForwardVelocity();
	void updateFriction();
	b2Vec2 getPosition();
	
	void hitDamage(PlayerAnimation* animation);
	void startContact();

	void HPUpdate(sf::Vector2f center);
	void collision(PlayerAnimation* animation, FractalRenderer* map);

};
