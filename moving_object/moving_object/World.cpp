#include "World.h"


World::World() 
{
	gravity = b2Vec2(0.0f, -5.0f);

	 m_world = new b2World(gravity);
};