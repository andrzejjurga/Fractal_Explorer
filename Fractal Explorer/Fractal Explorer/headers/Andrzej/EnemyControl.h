#pragma once
#include <vector>
#include <iostream>
#include "Enemy.h"
#include "Player.h"
#include "Animation.h"
#include "World.h"
#include <SFML/Graphics.hpp>

class EnemyControl
{
public:
	vector<Animation> animationTab;
	vector<Enemy> enemyTab;

	EnemyControl();

	void addEnemy(World * world, Animation * animation);

	void update(World* world, Player* player, sf::RenderWindow* window, Animation* animation);

};