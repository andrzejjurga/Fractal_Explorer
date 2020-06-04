/*
 *author: Sebastian Jerzykiewicz
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "Animation.h"

class PauseState : public State
{
public:
    PauseState(GameDataRef data);
    
    void Init();
    
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
    
    int GetPressedItem() {return selectedItemIndex;}
    void MoveUp();
    void MoveDown();
    
private:
    GameDataRef _data;
    sf::Sprite _background;
    sf::Font _font;
    sf::Text _menu[MAX_NUMBER_OF_ITEMS];
    int selectedItemIndex;
    Animation _animation;
};
