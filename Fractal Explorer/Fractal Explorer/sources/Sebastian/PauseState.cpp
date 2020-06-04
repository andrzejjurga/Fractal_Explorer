/*
 *author: Sebastian Jerzykiewicz
 */

#include "PauseState.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"

#include <iostream>
#include <sstream>

PauseState::PauseState(GameDataRef data) : _data(data), _animation(PAUSE_BG_ANIMATION_FILE_PATH, 45, 80, 36, 0.1f)
{
    
}

void PauseState::Init()
{
    _animation.sprite.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    _animation.sprite.setOrigin(_animation.sprite.getGlobalBounds().width / 2.0f, _animation.sprite.getGlobalBounds().height / 2.0f);
    _animation.sprite.setScale(16.0f, 16.0f);
    
    
    //this->_data->assets.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILE_PATH);
    this->_data->assets.LoadFont("Pause Font", FONT_FILE_PATH);
    
    //this->_background.setTexture(this->_data->assets.GetTexture("Pause Background"));
    
    _menu[0].setFont(this->_data->assets.GetFont("Pause Font"));
    _menu[0].setCharacterSize(50);
    _menu[0].setFillColor(sf::Color::Blue);//(50, 70, 170));
    _menu[0].setString(L"Wznów");
    _menu[0].setOutlineColor(sf::Color::White);
    _menu[0].setOutlineThickness(2);
    _menu[0].setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1);
    _menu[0].setOrigin(_menu[0].getGlobalBounds().width / 2.0f, _menu[0].getGlobalBounds().height / (MAX_NUMBER_OF_ITEMS + 1) * 1);
    
    _menu[1].setFont(this->_data->assets.GetFont("Pause Font"));
    _menu[1].setCharacterSize(50);
    _menu[1].setFillColor(sf::Color::Red);//(50, 70, 170));
    _menu[1].setString("Opcje");
    _menu[1].setOutlineColor(sf::Color::White);
    _menu[1].setOutlineThickness(0);
    _menu[1].setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2);
    _menu[1].setOrigin(_menu[1].getGlobalBounds().width / 2.0f, _menu[1].getGlobalBounds().height / (MAX_NUMBER_OF_ITEMS + 1) * 2);
    
    _menu[2].setFont(this->_data->assets.GetFont("Pause Font"));
    _menu[2].setCharacterSize(50);
    _menu[2].setFillColor(sf::Color::Red);//(50, 70, 170));
    _menu[2].setString(L"Powrót");
    _menu[2].setOutlineColor(sf::Color::White);
    _menu[2].setOutlineThickness(0);
    _menu[2].setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 3);
    _menu[2].setOrigin(_menu[2].getGlobalBounds().width / 2.0f, _menu[2].getGlobalBounds().height / (MAX_NUMBER_OF_ITEMS + 1) * 3);
    
    selectedItemIndex = 0;
    
}

void PauseState::HandleInput()
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
                    this->_data->machine.RemoveState();
                    break;
                case sf::Keyboard::Up:
                    PauseState::MoveUp();
                    break;
                case sf::Keyboard::Down:
                    PauseState::MoveDown();
                    break;
                case sf::Keyboard::Return:
                    switch (PauseState::GetPressedItem())
                {
                    case 0:
                        std::cout << "Resume button has been pressed" << std::endl;
                        this->_data->machine.RemoveState();
                        
                        break;
                    case 1:
                        std::cout << "Options button has been pressed" << std::endl;
                        
                        break;
                    case 2:
                        std::cout << "Home button has been pressed" << std::endl;
                        this->_data->machine.RemoveState();
                        this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
                        break;
                }
                    
                    
            }
                
        }
        
    }
}

void PauseState::Update(float dt)
{
    _animation.AnimationUpdate();
}

void PauseState::Draw(float dt)
{
    this->_data->window.clear();
    
    this->_data->window.draw(this->_animation.sprite);
    
    //this->_data->window.draw(this->_background);
    
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        this->_data->window.draw(_menu[i]);
    }
    
    this->_data->window.display();
}

void PauseState::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        _menu[selectedItemIndex].setFillColor(sf::Color::Red);
        _menu[selectedItemIndex].setOutlineThickness(0);
        selectedItemIndex--;
        _menu[selectedItemIndex].setFillColor(sf::Color::Blue);
        _menu[selectedItemIndex].setOutlineThickness(2);
    }
}

void PauseState::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        _menu[selectedItemIndex].setFillColor(sf::Color::Red);
        _menu[selectedItemIndex].setOutlineThickness(0);
        selectedItemIndex++;
        _menu[selectedItemIndex].setFillColor(sf::Color::Blue);
        _menu[selectedItemIndex].setOutlineThickness(2);
    }
}
