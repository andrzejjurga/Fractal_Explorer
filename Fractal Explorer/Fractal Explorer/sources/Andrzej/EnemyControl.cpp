#include "EnemyControl.h"

EnemyControl::EnemyControl()
{
	
}

void EnemyControl::addEnemy(World* world, Animation* animation, FractalRenderer* map)
{
	Enemy enemy(world, animation, map, 200, 400);
	enemyTab.push_back(enemy);

}

void EnemyControl::update(World* world, Player* player, sf::RenderWindow* window, Animation* animation, FractalRenderer* map, Explosion* exp)
{
	for (int i = 0; i < enemyTab.size(); i++)
	{
		if (enemyTab[i].HP <= 0)
		{
			forRemoval.insert(&enemyTab[i]);
			enemyTab.erase(enemyTab.begin()+i);
			exp->amount = 0;
			exp->sprite.setPosition(sf::Vector2f(enemyTab[i].position.x * PPM, enemyTab[i].position.y * PPM));
			window->draw(exp->sprite);
		}
		else
		{
			enemyTab[i].enemyUpdate(animation, player, map);
			window->draw(animation->sprite);
		}
	}
}
