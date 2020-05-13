#include "Player.h"
#include <cmath>

Player::Player(World* swiat, float X, float Y)
{
	bodyDef.type = b2_dynamicBody; //okreœlenie typu cia³a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X / swiat->PPM, Y / swiat->PPM); //pozycja pocz¹tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia³a do œwiata
	//dynamicBox.SetAsBox((100.0f / swiat->PPM) /2, (100.0f / swiat->PPM) / 2); //tworzenie obiektu z kolizjami
	vartices[0].Set(5 / swiat->PPM, -70 / swiat->PPM);
	vartices[1].Set(20 / swiat->PPM, 20 / swiat->PPM);
	vartices[2].Set(40 / swiat->PPM, 10 / swiat->PPM);
	vartices[3].Set(40 / swiat->PPM, -10 / swiat->PPM);
	vartices[4].Set(-40 / swiat->PPM, -10 / swiat->PPM);
	vartices[5].Set(-40 / swiat->PPM, 10 / swiat->PPM);
	vartices[6].Set(-20 / swiat->PPM, 20 / swiat->PPM);
	vartices[7].Set(-5 / swiat->PPM, -70 / swiat->PPM);
	shipShape.Set(vartices, 8);
	fixtureDef.shape = &shipShape;
	fixtureDef.density = 1; //gêstoœæ
	fixtureDef.friction = 0.6f; //tarcie
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia³a
}

void Player::playerUpdate(Animation* animation)
{
	position = body->GetPosition();
	angle = body->GetAngle();
	animation->AnimationUpdate();
	animation->sprite.setRotation(body->GetAngle() * 57.295779513082320876f);
	animation->sprite.setPosition(position.x * 30, position.y * 30);
	updateFriction();
	currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	currentSpeed = -1 * b2Dot(getForwardVelocity(), currentForwardNormal);
	
	if (Right == true)
		body->ApplyTorque(20, true);
	if (Left == true)
		body->ApplyTorque(-20, true);
	if (Up == true && currentSpeed<20)
		body->ApplyForce(b2Vec2(50 * sin(body->GetAngle()), -50 * cos(body->GetAngle())), body->GetWorldCenter(), true);
	if (Down == true && currentSpeed > -10)
		body->ApplyForce(b2Vec2(-50 * sin(body->GetAngle()), 50 * cos(body->GetAngle())), body->GetWorldCenter(), true);
}

b2Vec2 Player::getLateralValocity()
{
	currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
	if (impulse.Length() > maxLateralImpulse)
		impulse *= maxLateralImpulse / impulse.Length()*2;
	return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Player::getForwardVelocity() {
	currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}

void Player::updateFriction() 
{
	impulse = body->GetMass() * -getLateralValocity();
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
	body->ApplyAngularImpulse(0.01f * body->GetInertia() * -body->GetAngularVelocity(), true);
	currentForwardNormal = getForwardVelocity();
	float currentForwardSpeed = currentForwardNormal.Normalize();
	float dragForceMagnitude = -2 * currentForwardSpeed;
	body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
}

b2Vec2 Player::getPosition()
{
	return body->GetPosition();
}