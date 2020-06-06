#include "Explosion.h"

Explosion::Explosion()
{
    texture.loadFromFile("./Resources/Images/explosion.png");
    rectSourceSprite = sf::IntRect(0, 0, 140, 140);
    sprite = sf::Sprite(texture, rectSourceSprite);
    sprite.setOrigin(70, 70);
    amount = 0;
    sprite.setScale(2, 2);
    sprite.setPosition(-10000, -10000);
}

void Explosion::update()
{
    sprite.setTextureRect(
        sf::IntRect(rectSourceSprite.left += 140,0,140,140));
    if (rectSourceSprite.left >= 3780)
        rectSourceSprite.left = 0;
    if (amount > 27)
        sprite.setColor(sf::Color(0, 0, 0, 0));
    else
        sprite.setColor(sf::Color(255, 255, 255, 255));
    amount++;
}