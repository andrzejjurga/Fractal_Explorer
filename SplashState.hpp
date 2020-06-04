/*
 *author: Sebastian Jerzykiewicz
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Sounds.hpp"

class SplashState : public State
{
public:
	SplashState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	sf::Clock _clock;

	sf::Sprite _background;
    
    sf::Font _font;
    
    sf::Text _text;
    
    Sounds _sound;
    
};