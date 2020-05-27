#include "Enemy.h"

Enemy::Enemy(World* swiat, float X, float Y)
{
	bodyDef.type = b2_dynamicBody; //okreœlenie typu cia³a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X / PPM, Y / PPM); //pozycja pocz¹tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia³a do œwiata
	fixtureDef.restitution = 0.2f;
	vartices[0].Set(5 / PPM, -70 / PPM);//wieszcho³ki wielok¹ta kolizji 
	vartices[1].Set(10 / PPM, 20 / PPM);
	vartices[2].Set(40 / PPM, -10 / PPM);
	vartices[3].Set(40 / PPM, -50 / PPM);
	vartices[4].Set(-40 / PPM, -50 / PPM);
	vartices[5].Set(-40 / PPM, -10 / PPM);
	vartices[6].Set(-10 / PPM, 20 / PPM);
	vartices[7].Set(-5 / PPM, -70 / PPM);
	shipShape.Set(vartices, 8);
	enginePower = 30.f;
	maxLateralImpulse = 2.5f;
	fixtureDef.shape = &shipShape;
	fixtureDef.density = 1; //gêstoœæ
	fixtureDef.friction = 0.01f; //tarcie
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia³a
	updateFriction();
	body->SetUserData(this);
}

void Enemy::enemyUpdate(Animation* animation, Player* gracz)
{
	position = body->GetPosition();
	angle = body->GetAngle();
	animation->AnimationUpdate();
	animation->sprite.setRotation(angle * RADTODEG);
	animation->sprite.setPosition(position.x * PPM, position.y * PPM);
	updateFriction();
	currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	currentSpeed = -1 * b2Dot(getForwardVelocity(), currentForwardNormal);

	pleyerPosition = gracz->getPosition() - position;
	playerAngle = atan2f(pleyerPosition.x, -pleyerPosition.y);
	calAngle = angle + body->GetAngularVelocity() / 3;
	totalRotation = playerAngle - calAngle;

	while (totalRotation < -180 * DEGTORAD)
		totalRotation += 360 * DEGTORAD;
	while (totalRotation > 180 * DEGTORAD)
		totalRotation -= 360 * DEGTORAD;

	body->ApplyTorque(body->GetInertia() * totalRotation * 30, true);
	if (currentSpeed < 15)
		body->ApplyForce(b2Vec2(enginePower * sin(angle), enginePower * -cos(angle)), body->GetWorldCenter(), true);

}

b2Vec2 Enemy::getLateralValocity()
{
	currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
	if (impulse.Length() > maxLateralImpulse)
		impulse *= maxLateralImpulse / impulse.Length() * 2;
	return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Enemy::getForwardVelocity() {
	currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}

void Enemy::updateFriction()
{
	impulse = body->GetMass() * -getLateralValocity();
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
	body->ApplyAngularImpulse(0.01f * body->GetInertia() * -body->GetAngularVelocity(), true);
	currentForwardNormal = getForwardVelocity();
	float currentForwardSpeed = currentForwardNormal.Normalize();
	float dragForceMagnitude = -2 * currentForwardSpeed;
	body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
}