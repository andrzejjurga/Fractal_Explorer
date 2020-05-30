#include "Animation.h"

Animation::Animation(){}

Animation::Animation(string _file, float _height, float _width, int _amount, float _speed) :
    file{ _file }, height{ _height }, width{ _width }, amount{ _amount }, speed{_speed}
{
    texture.setRepeated(true);
    texture.loadFromFile(file);
    rectSourceSprite=sf::IntRect(0, 0, width, height);
    sprite=sf::Sprite(texture, rectSourceSprite);
    sprite.setOrigin(width / 2, height / 2);
}

void Animation::AnimationUpdate(sf::Vector2f position)
{
    if (clock.getElapsedTime().asSeconds() > speed) {
        if (rectSourceSprite.left >= width * (amount - 1))
            rectSourceSprite.left = 0;
        else
            rectSourceSprite.left += width;
        sprite.setTextureRect(
            sf::IntRect(
                rectSourceSprite.left + (int)position.x,
                rectSourceSprite.top + (int)position.y,
                rectSourceSprite.width,
                rectSourceSprite.height
            )
        );
        clock.restart();
    }
}

Animation& Animation::operator=(const Animation& obj)
{
    if (&obj != this)
    {
        clock = obj.clock;
        texture = obj.texture;
        rectSourceSprite = obj.rectSourceSprite;
        file = obj.file;
        height = obj.height;
        width = obj.width;
        amount = obj.amount;
        speed = obj.speed;
        sprite = obj.sprite;
    }
    return *this;
}