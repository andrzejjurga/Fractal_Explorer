#include "Enemy.h"

Enemy::Enemy(World* swiat, float X, float Y)
{
	bodyDef.type = b2_dynamicBody; //okre�lenie typu cia�a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X / swiat->PPM, Y / swiat->PPM); //pozycja pocz�tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia�a do �wiata
	dynamicBox.SetAsBox((100.0f / swiat->PPM) / 2, (100.0f / swiat->PPM) / 2); //tworzenie obiektu z kolizjami
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1; //g�sto��
	fixtureDef.friction = 0.6f; //tarcie
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia�a

}

void Enemy::enemyUpdate(Animation* animation)
{
	position = body->GetPosition();
	angle = body->GetAngle();
	animation->AnimationUpdate();
	animation->sprite.setRotation(body->GetAngle() * 57.295779513082320876f);
	animation->sprite.setPosition(position.x * 30, position.y * 30);
	
}
