/*
 *author: Sebastian Jerzykiewicz
 */

#include "SplashState.hpp"

#include <iostream>
#include <sstream>

#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"


SplashState::SplashState(GameDataRef data) : _data(data), _sound(SPLASH_SCREEN_SOUND_FILE_PATH)
{

}

void SplashState::Init()
{
    _sound.sound.play();
    
	this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILE_PATH);

	_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
    
    this->_data->assets.LoadFont("Splash State Font", FONT_FILE_PATH);
    
    _text.setFont(this->_data->assets.GetFont("Splash State Font"));
    _text.setString("PROJEKT PROGRAMOWANIE");
    _text.setCharacterSize(80);
    _text.setFillColor(sf::Color::Red);
    _text.setOutlineColor(sf::Color::White);
    _text.setOutlineThickness(5);
    _text.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    _text.setOrigin(_text.getGlobalBounds().width / 2.0f, _text.getGlobalBounds().height / 2.0f);
}

void SplashState::HandleInput()
{
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

	}

}

void SplashState::Update(float dt)
{
	if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
        //switch state
        this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
	}
}

void SplashState::Draw(float dt)
{
	this->_data->window.clear();

	this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_text);

	this->_data->window.display();
}

