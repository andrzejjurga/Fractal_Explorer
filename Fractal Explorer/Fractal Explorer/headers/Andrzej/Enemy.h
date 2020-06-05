#pragma once
#include <iostream>
#include <box2d/box2d.h>
#include "Animation.h"
#include "World.h"
#include "Player.h"
#include <FractalCollision.h>
#include <MandelViewer.h>

using namespace std;

class Enemy
{
public:
	b2BodyDef bodyDef;
	b2PolygonShape shipShape;//kszta�t obiektu
	b2Vec2 vartices[8];//tablica wieszcho�k�w
	b2Body* body;
	b2FixtureDef fixtureDef;
	b2Vec2 position;
	float angle;
	
	//w�a�ciwo�ci kinetyczne statku
	b2Vec2 currentRightNormal;
	b2Vec2 impulse;
	b2Vec2 currentForwardNormal;
	b2Vec2 currentForwardSpeed;
	float currentSpeed;
	float maxLateralImpulse = 0.5f;
	float enginePower = 30.f;
	bool connect = false;
	//namierzanie gracza
	b2Vec2 pleyerPosition; //pozycja gracza
	float playerAngle; //kont na lini kt�rego le�y gracz
	float totalRotation; //ca�y kont potrzebny do ustawienia si� przodem do gracza
	float calAngle; //kont wyliczny z wyprzedzeniem dla torqa

	int HP; //Punkty �ycia statku
	FractalCollision fractalCollision;//kolizje 
	//konstruktor
	Enemy(World* swiat, Animation* animation, FractalRenderer* map, float X, float Y);

	void enemyUpdate(Animation* animation, Player* gracz, FractalRenderer* map);
	void updateFriction();//zapobiega "�lizganiu" si� statku na boki

	b2Vec2 getLateralValocity();//pr�dko�� ruchu bocznego
	b2Vec2 getForwardVelocity();//pr�dkos� na prz�d i do ty�u

	void hitDamage(Animation* animation);
	void collision(Animation* animation, FractalRenderer* map);
	~Enemy();
};
