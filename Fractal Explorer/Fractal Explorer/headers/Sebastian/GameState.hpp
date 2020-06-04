/*
 *author: Sebastian Jerzykiewicz
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "Animation.h"

class GameState : public State
{
public:
    GameState(GameDataRef data);
    
    void Init();
    
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
    
private:
    GameDataRef _data;
    sf::Sprite _background;
    sf::Font _font;
    sf::Text _text;
    sf::Clock _clock;
    sf::Text _numbers;
    int i = 1;
    Animation _animation;
};
