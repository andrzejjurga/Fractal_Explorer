#pragma once
#include <vector>
#include <iostream>
#include "Enemy.h"
#include "Player.h"
#include "Animation.h"
#include "World.h"
#include <SFML/Graphics.hpp>
#include <set>
#include <FractalCollision.h>
#include <MandelViewer.h>
#include "Explosion.h"

class EnemyControl
{
public:
	std::set<Enemy*> forRemoval;
	vector<Enemy> enemyTab;

	EnemyControl();

	void addEnemy(World * world, Animation * animation, FractalRenderer* map);

	void update(World* world, Player* player, sf::RenderWindow* window, Animation* animation, FractalRenderer* map, Explosion* exp);

};