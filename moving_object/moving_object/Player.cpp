#include "Player.h"

Player::Player(World* swiat, float X, float Y)
{
	bodyDef.type = b2_dynamicBody; //okre�lenie typu cia�a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X / swiat->PPM, Y / swiat->PPM); //pozycja pocz�tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia�a do �wiata
	dynamicBox.SetAsBox((100.0f / swiat->PPM) /2, (100.0f / swiat->PPM) / 2); //tworzenie obiektu z kolizjami
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f; //g�sto��
	fixtureDef.friction = 0.3f; //tarcie
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia�a
}

void Player::playerUpdate(Animation* animation)
{
	position = body->GetPosition();
	angle = body->GetAngle();
	animation->sprite.setPosition(position.x * 20, position.y * 20);
	animation->AnimationUpdate();
	cout << position.x << " " << position.y << endl;
}
