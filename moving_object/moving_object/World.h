#pragma once
#include <iostream>
#include <Box2d/Box2D.h>

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class World
{
public:

	const float PPM = 30.f; //konwersja piksele/metry

	b2Vec2 gravity;
	b2World * m_world;
	World();

};
