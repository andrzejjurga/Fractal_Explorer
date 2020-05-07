#include "Animation.h"

Animation::Animation(){}

Animation::Animation(string _file, float _height, float _width, int _amount, float _speed) :
    file{ _file }, height{ _height }, width{ _width }, amount{ _amount }, speed{_speed}
{
    texture.loadFromFile(file);
    rectSourceSprite=sf::IntRect(0, 0, width, height);
    sprite=sf::Sprite(texture, rectSourceSprite);
}

void Animation::AnimationUpdate()
{
    if (clock.getElapsedTime().asSeconds() > speed) {
        if (rectSourceSprite.left == width * (amount - 1))
            rectSourceSprite.left = 0;
        else
            rectSourceSprite.left += width;
        sprite.setTextureRect(rectSourceSprite);
        clock.restart();
    }
}