#include "Player.h"
#include <cmath>

Player::Player(World* swiat, PlayerAnimation* animation, float X, float Y)
{
	HP = 100;
	bodyDef.type = b2_dynamicBody; //okreœlenie typu cia³a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X / PPM, Y / PPM); //pozycja pocz¹tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia³a do œwiata
	fixtureDef.restitution = 0.2f;//odbijanie siê obiektów
	vartices[0].Set(2 / PPM, -40 / PPM);
	vartices[1].Set(10 / PPM, 20 / PPM);
	vartices[2].Set(30 / PPM, 10 / PPM);
	vartices[3].Set(20 / PPM, -10 / PPM);
	vartices[4].Set(-20 / PPM, -10 / PPM);
	vartices[5].Set(-30 / PPM, 10 / PPM);
	vartices[6].Set(-10 / PPM, 20 / PPM);
	vartices[7].Set(-2 / PPM, -40 / PPM);
	shipShape.Set(vartices, 8);
	fixtureDef.shape = &shipShape; 
	enginePower = 50.f;
	maxLateralImpulse = 2.5f;
	fixtureDef.density = 4; //gêstoœæ
	fixtureDef.friction = 0.6f; //tarcie
	angle = body->GetAngle();
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia³a
	body->SetUserData(this);
	animation->sprite.setScale(sf::Vector2f(2, 2));
}

void Player::playerUpdate(PlayerAnimation* animation)
{
	position = body->GetPosition();
	angle = body->GetAngle();
	animation->playerAnimationUpdate();
	animation->sprite.setRotation(angle * RADTODEG);
	animation->sprite.setPosition(position.x * PPM, position.y * PPM);
	updateFriction();
	currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	currentSpeed = -1 * b2Dot(getForwardVelocity(), currentForwardNormal);

	if (Right == true)
		body->ApplyTorque(15, true);
	if (Left == true)
		body->ApplyTorque(-15, true);
	if (Up == true && currentSpeed<10)
		body->ApplyForce(b2Vec2(enginePower * sin(body->GetAngle()), enginePower * -cos(body->GetAngle())), body->GetWorldCenter(), true);
	if (Down == true && currentSpeed > -5)
		body->ApplyForce(b2Vec2(enginePower * -sin(body->GetAngle()), enginePower * cos(body->GetAngle())), body->GetWorldCenter(), true);
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

void Player::hitDamage(PlayerAnimation* animation)
{
	if (abs(getForwardVelocity().x) + abs(getForwardVelocity().y) > 10.f)
		//cout << "oof" << endl;
		animation->sprite.setColor(sf::Color(255, 0, 0));
}

void Player::startContact()
{
	connect = true;
}