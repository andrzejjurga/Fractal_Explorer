#include "Player.h"

Player::Player(World* swiat, float X, float Y)
{
	bodyDef.type = b2_dynamicBody; //okre�lenie typu cia�a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X, Y); //pozycja pocz�tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia�a do �wiata
	dynamicBox.SetAsBox(1.0f, 1.0f); //tworzenie obiektu z kolizjami
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f; //g�sto��
	fixtureDef.friction = 0.3f; //tarcie
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia�a
}

