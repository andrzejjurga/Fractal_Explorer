/*
 *author: Sebastian Jerzykiewicz
 */

#include "GameState.hpp"
#include "PauseState.hpp"

#include <iostream>
#include <sstream>

GameState::GameState(GameDataRef data) : _data(data)//, _animation(GAME_BG_ANIMATION_FILE_PATH, 720, 1280, 12, 0.1f)
{
    
}

void GameState::Init()
{

    
    this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILE_PATH);
    this->_data->assets.LoadFont("Game Font", FONT_FILE_PATH);
    
    this->_background.setTexture(this->_data->assets.GetTexture("Game Background"));
    
    _numbers.setFont(this->_data->assets.GetFont("Game Font"));
    _numbers.setString("1");
    _numbers.setCharacterSize(50);
    _numbers.setFillColor(sf::Color::Red);
    _numbers.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 1.5f);
    _numbers.setOrigin(_numbers.getGlobalBounds().width / 2.0f, _numbers.getGlobalBounds().height / 1.5f);
    
    _text.setFont(this->_data->assets.GetFont("Game Font"));
    _text.setString("GRA");
    _text.setCharacterSize(80);
    _text.setFillColor(sf::Color::Red);
    _text.setOutlineColor(sf::Color::White);
    _text.setOutlineThickness(5);
    _text.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    _text.setOrigin(_text.getGlobalBounds().width / 2.0f, _text.getGlobalBounds().height / 2.0f);
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
     if (_clock.getElapsedTime().asSeconds() > 1.0f)
     {
         i++;
         _numbers.setString(std::to_string(i));
         _clock.restart();
     }
     _animation.AnimationUpdate();
}

void GameState::Draw(float dt)
{
    //this->_data->window.draw(this->_animation.sprite);
    
    this->_data->window.draw(this->_background);
    
    this->_data->window.draw(this->_text);
    this->_data->window.draw(_numbers);
    
    this->_data->window.display();
}




