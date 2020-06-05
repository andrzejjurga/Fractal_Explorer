#include "PlayerAnimation.h"

void PlayerAnimation::playerAnimationUpdate()
{
    if (Right == true || Left == true || Up == true || Down == true)
    {
        rectSourceSprite.height = height;
    }
    else
    {
        rectSourceSprite.height = 32;

    }
    if (clock.getElapsedTime().asSeconds() > speed) {
        if (rectSourceSprite.left == width * (amount - 1))
            rectSourceSprite.left = 0;
        else
            rectSourceSprite.left += width;
        sprite.setTextureRect(rectSourceSprite);
        clock.restart();
    }
}

