#include "EnemyControl.h"

EnemyControl::EnemyControl()
{
	
}

void EnemyControl::addEnemy(World* world, Animation* animation)
{
	//Animation enemyShip("./resources/enemy_ship.png", 44, 28, 4, 0.1f);
	//animationTab.push_back(enemyShip);
	Enemy enemy(world, animation, 200, 400);
	enemyTab.push_back(enemy);
}

void EnemyControl::update(World* world, Player* player, sf::RenderWindow* window, Animation* animation)
{
	for (int i = 0; i < enemyTab.size(); i++)
	{
		enemyTab[i].enemyUpdate(animation, player);
		window->draw(animation->sprite);
	}
}
