#pragma once
#include <iostream>
#include <Box2d/Box2D.h>

class World
{
public:

	const float PPM = 30.f; //konwersja piksele/metry

	b2Vec2 gravity;
	b2World * m_world;
	World();

};
