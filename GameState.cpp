/*
 *author: Sebastian Jerzykiewicz
 */

#include "GameState.hpp"
#include "PauseState.hpp"

#include "World.h"
#include "Player.h"
#include "Animation.h"
#include "PlayerAnimation.h"
#include "FractalChart.h"
#include "Enemy.h"
#include "Music.h"
#include "EnemyControl.h"

#include <iostream>
#include <sstream>

GameState::GameState(GameDataRef data) : _data(data)
{
    
}

void GameState::Init()
{

}

void GameState::HandleInput()
{
    sf::Event event;
    
    while (this->_data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            this->_data->window.close();
        }
        
        switch (event.type)
        {
            case sf::Event::KeyReleased:
                switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                    std::cout << "Pause" << std::endl;
                    this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
                    
                    break;
            }
                
        }
        
    }
}

void GameState::Update(float dt)
{

}

void GameState::Draw(float dt)
{

}




