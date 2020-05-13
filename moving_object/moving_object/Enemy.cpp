#include "Enemy.h"

Enemy::Enemy(World* swiat, float X, float Y)
{
	bodyDef.type = b2_dynamicBody; //okreœlenie typu cia³a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X / swiat->PPM, Y / swiat->PPM); //pozycja pocz¹tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia³a do œwiata
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
	fixtureDef.friction = 0.01f; //tarcie
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia³a
	updateFriction();
}

void Enemy::enemyUpdate(Animation* animation, Player* gracz)
{
	position = body->GetPosition();
	angle = body->GetAngle();
	animation->AnimationUpdate();
	animation->sprite.setRotation(angle * 57.295779513082320876f);
	animation->sprite.setPosition(position.x * 30, position.y * 30);
	updateFriction();
	currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	currentSpeed = -1 * b2Dot(getForwardVelocity(), currentForwardNormal);

	pleyerPosition = gracz->getPosition() - position;
	playerAngle = atan2f(pleyerPosition.x, -pleyerPosition.y);
	body->SetTransform(position, playerAngle);
	calAngle = angle + body->GetAngularVelocity() / 3;
	totalRotation = playerAngle - calAngle;
	while (totalRotation < -180 * DEGTORAD)
		totalRotation += 360 * DEGTORAD;
	while (totalRotation > 180 * DEGTORAD)
		totalRotation -= 360 * DEGTORAD;
	torque = body->GetInertia() * totalRotation*30;
	body->ApplyTorque(totalRotation < 0 ? -10 : 10, true);
	cout << torque << endl;
	//body->ApplyTorque(torque, true);
	//if (currentSpeed < 25)
		body->ApplyForce(b2Vec2(300 * sin(angle), -300 * cos(angle)), body->GetWorldCenter(), true);

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