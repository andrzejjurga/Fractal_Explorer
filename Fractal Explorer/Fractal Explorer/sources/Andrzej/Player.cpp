#include "Player.h"


Player::Player(World* swiat, PlayerAnimation* animation, FractalRenderer* map, float X, float Y)
{
	HP = 100;
	HPSprite.setPosition(100, 100);
	HPSprite.setSize(sf::Vector2f(150, 40));
	HPSprite.setFillColor(sf::Color(240, 0, 0));
	HPSpriteOutline.setPosition(100, 100);
	HPSpriteOutline.setSize(sf::Vector2f(152, 42));
	HPSpriteOutline.setFillColor(sf::Color(0, 0, 0, 0));
	HPSpriteOutline.setOutlineColor(sf::Color::Black);
	HPSpriteOutline.setOutlineThickness(5);

	bodyDef.type = b2_dynamicBody; //okreœlenie typu cia³a dynamiczne/kinetyczne/statyczne
	bodyDef.position.Set(X / PPM, Y / PPM); //pozycja pocz¹tkowa
	body = swiat->m_world->CreateBody(&bodyDef); //dodanie cia³a do œwiata
	fixtureDef.restitution = 0.2f;//odbijanie siê obiektów
	vertices[0].Set(2 / PPM, -40 / PPM);
	vertices[1].Set(10 / PPM, 20 / PPM);
	vertices[2].Set(30 / PPM, 10 / PPM);
	vertices[3].Set(20 / PPM, -10 / PPM);
	vertices[4].Set(-20 / PPM, -10 / PPM);
	vertices[5].Set(-30 / PPM, 10 / PPM);
	vertices[6].Set(-10 / PPM, 20 / PPM);
	vertices[7].Set(-2 / PPM, -40 / PPM);
	shipShape.Set(vertices, 8);
	fixtureDef.shape = &shipShape; 
	enginePower = 50.f;
	maxLateralImpulse = 2.5f;
	fixtureDef.density = 2; //gêstoœæ
	fixtureDef.friction = 0.6f; //tarcie
	angle = body->GetAngle();
	body->CreateFixture(&fixtureDef); //dodanie kolizji do cia³a
	body->SetUserData(this);
	animation->sprite.setScale(sf::Vector2f(2, 2));
	fractalCollision.setFractal(*map);
}

void Player::playerUpdate(PlayerAnimation* animation, FractalRenderer* map)
{
	position = body->GetPosition();
	angle = body->GetAngle();
	animation->playerAnimationUpdate();
	animation->sprite.setRotation(angle * RADTODEG);
	animation->sprite.setPosition(position.x * PPM, position.y * PPM);
	updateFriction();
	currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	//kolizje
	if (abs(currentSpeed - (-1 * b2Dot(getForwardVelocity(), currentForwardNormal))) > 0.30)
		hitDamage(animation);
	else
		animation->sprite.setColor(sf::Color(255, 255, 255));
	collision(animation, map);
	
	currentSpeed = -1 * b2Dot(getForwardVelocity(), currentForwardNormal);

	if (Right == true && HP > 0)
		body->ApplyTorque(15, true);
	if (Left == true && HP > 0)
		body->ApplyTorque(-15, true);
	if (Up == true && currentSpeed<10 && HP > 0)
		body->ApplyForce(b2Vec2(enginePower * sin(body->GetAngle()), enginePower * -cos(body->GetAngle())), body->GetWorldCenter(), true);
	if (Down == true && currentSpeed > -5 && HP > 0)
		body->ApplyForce(b2Vec2(enginePower * -sin(body->GetAngle()), enginePower * cos(body->GetAngle())), body->GetWorldCenter(), true);
	if (HP <= 0)
		animation->sprite.setColor(sf::Color(0, 0, 0, 0));
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
		animation->sprite.setColor(sf::Color(255, 0, 0));
		HP -= abs(currentSpeed - (-1 * b2Dot(getForwardVelocity(), currentForwardNormal)));
		if (HP <= 0)
		{
			HP = 0;
		}
}

void Player::startContact()
{
	connect = true;
}

void Player::HPUpdate(sf::Vector2f center)
{
	HPSprite.setPosition(center.x + 480, center.y + 300);
	HPSprite.setSize(sf::Vector2f(HP * 1.5, 40));
	HPSpriteOutline.setPosition(center.x + 479, center.y + 299);
}

void Player::collision(PlayerAnimation* animation, FractalRenderer* map)//rozwi¹zanie tymaczasowe
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