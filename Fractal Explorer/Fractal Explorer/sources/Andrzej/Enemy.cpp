#include "Enemy.h"

Enemy::Enemy(World* swiat, Animation* animation, FractalRenderer* map, float X, float Y)
{
	HP = 20;
	bodyDef.type = b2_dynamicBody; //okreœlenie typu cia³a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X / PPM, Y / PPM); //pozycja pocz¹tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia³a do œwiata
	fixtureDef.restitution = 0.2f;
	vartices[0].Set(2 / PPM, -40 / PPM);//wieszcho³ki wielok¹ta kolizji 
	vartices[1].Set(5 / PPM, 15 / PPM);
	vartices[2].Set(25 / PPM, 0 / PPM);
	vartices[3].Set(25 / PPM, -25 / PPM);
	vartices[4].Set(-25 / PPM, -25 / PPM);
	vartices[5].Set(-25 / PPM, 0 / PPM);
	vartices[6].Set(-5 / PPM, 15 / PPM);
	vartices[7].Set(-2 / PPM, -40 / PPM);
	shipShape.Set(vartices, 8);
	enginePower = 30.f;
	maxLateralImpulse = 2.5f;
	fixtureDef.shape = &shipShape;
	fixtureDef.density = 2; //gêstoœæ
	fixtureDef.friction = 0.01f; //tarcie
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia³a
	updateFriction();
	body->SetUserData(this);
	animation->sprite.setScale(sf::Vector2f(2, 2));
	fractalCollision.setFractal(*map);
}

void Enemy::enemyUpdate(Animation* animation, Player* gracz, FractalRenderer* map)
{
	position = body->GetPosition();
	angle = body->GetAngle();
	animation->AnimationUpdate();
	animation->sprite.setRotation(angle * RADTODEG);
	animation->sprite.setPosition(position.x * PPM, position.y * PPM);
	updateFriction();
	currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	pleyerPosition = gracz->getPosition() - position;
	playerAngle = atan2f(pleyerPosition.x, -pleyerPosition.y);
	calAngle = angle + body->GetAngularVelocity() / 3;
	totalRotation = playerAngle - calAngle;

	while (totalRotation < -180 * DEGTORAD)
		totalRotation += 360 * DEGTORAD;
	while (totalRotation > 180 * DEGTORAD)
		totalRotation -= 360 * DEGTORAD;

	body->ApplyTorque(body->GetInertia() * totalRotation * 10, true);
	if (currentSpeed < 8)
		body->ApplyForce(b2Vec2(enginePower * sin(angle), enginePower * -cos(angle)), body->GetWorldCenter(), true);

	if (abs(currentSpeed - (-1 * b2Dot(getForwardVelocity(), currentForwardNormal))) > 0.30)
		hitDamage(animation);
	else
		animation->sprite.setColor(sf::Color(255, 255, 255));
	collision(animation, map);
	currentSpeed = -1 * b2Dot(getForwardVelocity(), currentForwardNormal);

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

void Enemy::hitDamage(Animation* animation)
{
	animation->sprite.setColor(sf::Color(255, 0, 0));
	HP -= abs(currentSpeed - (-1 * b2Dot(getForwardVelocity(), currentForwardNormal)));
	if (HP <= 0)
	{
		HP = 0;
	}
	cout << HP << endl;
}

Enemy::~Enemy()
{}

void Enemy::collision(Animation* animation, FractalRenderer* map)//rozwi¹zanie tymaczasowe
{
	if (map->belongsToSet({ position.x * PPM, position.y * PPM }))
	{
		animation->sprite.setColor(sf::Color(255, 0, 0));
		HP = 0;
	}
	else if (map->belongsToSet({ (1.5 * sin(body->GetAngle()) + position.x) * PPM,(1.5 * -cos(body->GetAngle()) + position.y) * PPM }))
	{
		animation->sprite.setColor(sf::Color(255, 0, 0));
		HP = 0;
	}
	else if (map->belongsToSet({ (0.6 * -sin(body->GetAngle()) + position.x) * PPM,(0.6 * cos(body->GetAngle()) + position.y) * PPM }))
	{
		animation->sprite.setColor(sf::Color(255, 0, 0));
		HP = 0;
	}
	else if (map->belongsToSet({ ((0.5 * -sin(body->GetAngle()) + position.x) * PPM) + 35,(0.5 * cos(body->GetAngle()) + position.y) * PPM }))
	{
		animation->sprite.setColor(sf::Color(255, 0, 0));
		HP = 0;
	}
	else
		animation->sprite.setColor(sf::Color(255, 255, 255));
}