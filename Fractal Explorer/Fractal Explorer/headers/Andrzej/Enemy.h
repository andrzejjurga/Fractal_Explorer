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
	b2PolygonShape shipShape;//kszta³t obiektu
	b2Vec2 vartices[8];//tablica wieszcho³ków
	b2Body* body;
	b2FixtureDef fixtureDef;
	b2Vec2 position;
	float angle;
	
	//w³aœciwoœci kinetyczne statku
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
	float playerAngle; //kont na lini którego le¿y gracz
	float totalRotation; //ca³y kont potrzebny do ustawienia siê przodem do gracza
	float calAngle; //kont wyliczny z wyprzedzeniem dla torqa

	int HP; //Punkty ¿ycia statku
	FractalCollision fractalCollision;//kolizje 
	//konstruktor
	Enemy(World* swiat, Animation* animation, FractalRenderer* map, float X, float Y);

	void enemyUpdate(Animation* animation, Player* gracz, FractalRenderer* map);
	void updateFriction();//zapobiega "œlizganiu" siê statku na boki

	b2Vec2 getLateralValocity();//prêdkoœæ ruchu bocznego
	b2Vec2 getForwardVelocity();//prêdkosæ na przód i do ty³u

	void hitDamage(Animation* animation);
	void collision(Animation* animation, FractalRenderer* map);
	~Enemy();
};
