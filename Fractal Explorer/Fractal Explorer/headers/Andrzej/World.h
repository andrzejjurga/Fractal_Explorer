#pragma once
#include <iostream>
#include <box2d/box2d.h>


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define PPM 30.f //konwersja piksele/metry

class World
{
public:
	b2Vec2 gravity;
	b2World * m_world;
	World();
};
