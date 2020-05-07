#include "Player.h"

Player::Player(World* swiat, float X, float Y)
{
	bodyDef.type = b2_dynamicBody; //okreœlenie typu cia³a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X, Y); //pozycja pocz¹tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia³a do œwiata
	dynamicBox.SetAsBox(1.0f, 1.0f); //tworzenie obiektu z kolizjami
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f; //gêstoœæ
	fixtureDef.friction = 0.3f; //tarcie
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia³a
}

