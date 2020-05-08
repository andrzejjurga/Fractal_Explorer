#include "Player.h"

Player::Player(World* swiat, float X, float Y)
{
	bodyDef.type = b2_dynamicBody; //okreœlenie typu cia³a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X / swiat->PPM, Y / swiat->PPM); //pozycja pocz¹tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia³a do œwiata
	dynamicBox.SetAsBox((100.0f / swiat->PPM) /2, (100.0f / swiat->PPM) / 2); //tworzenie obiektu z kolizjami
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f; //gêstoœæ
	fixtureDef.friction = 0.3f; //tarcie
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia³a
}

void Player::playerUpdate(Animation* animation)
{
	position = body->GetPosition();
	angle = body->GetAngle();
	animation->sprite.setPosition(position.x * 20, position.y * 20);
	animation->AnimationUpdate();
	cout << position.x << " " << position.y << endl;
}
