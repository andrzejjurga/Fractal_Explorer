/*
 *author: Sebastian Jerzykiewicz
 */

#include "scenes.h" //edit: Antoni Tretiakov

#include "MainMenuState.hpp"
#include "GameState.hpp"

#include <iostream>
#include <sstream>

MainMenuState::MainMenuState(GameDataRef data) : _data(data), _animation(MAIN_MENU_BG_ANIMATION_FILE_PATH, 45, 80, 36, 0.1f)
{
    
}

void MainMenuState::Init()
{
    
    _animation.sprite.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    _animation.sprite.setOrigin(_animation.sprite.getGlobalBounds().width / 2.0f, _animation.sprite.getGlobalBounds().height / 2.0f);
    _animation.sprite.setScale(16.0f, 16.0f);
    
    
    //this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILE_PATH);
    this->_data->assets.LoadFont("Main Menu Font", FONT_FILE_PATH);
    
    //this->_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
    
    _menu[0].setFont(this->_data->assets.GetFont("Main Menu Font"));
    _menu[0].setCharacterSize(50);
    _menu[0].setFillColor(sf::Color::Blue);//(50, 70, 170));
    _menu[0].setString("Graj");
    _menu[0].setOutlineColor(sf::Color::White);
    _menu[0].setOutlineThickness(2);
    _menu[0].setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1);
    _menu[0].setOrigin(_menu[0].getGlobalBounds().width / 2.0f, _menu[0].getGlobalBounds().height / (MAX_NUMBER_OF_ITEMS + 1) * 1);
    
    _menu[1].setFont(this->_data->assets.GetFont("Main Menu Font"));
    _menu[1].setCharacterSize(50);
    _menu[1].setFillColor(sf::Color::Red);//(50, 70, 170));
    _menu[1].setString("Opcje");
    _menu[1].setOutlineColor(sf::Color::White);
    _menu[1].setOutlineThickness(0);
    _menu[1].setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2);
    _menu[1].setOrigin(_menu[1].getGlobalBounds().width / 2.0f, _menu[1].getGlobalBounds().height / (MAX_NUMBER_OF_ITEMS + 1) * 2);
    
    _menu[2].setFont(this->_data->assets.GetFont("Main Menu Font"));
    _menu[2].setCharacterSize(50);
    _menu[2].setFillColor(sf::Color::Red);//(50, 70, 170));
    _menu[2].setString(L"Wyjœcie");
    _menu[2].setOutlineColor(sf::Color::White);
    _menu[2].setOutlineThickness(0);
    _menu[2].setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 3);
    _menu[2].setOrigin(_menu[2].getGlobalBounds().width / 2.0f, _menu[2].getGlobalBounds().height / (MAX_NUMBER_OF_ITEMS + 1) * 3);
    
    selectedItemIndex = 0;
    
}

void MainMenuState::HandleInput()
{
    sf::Event event;
    
    while (this->_data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            scenes::currentScene = scene::exit;// Edit: Antoni Tretiakov
            this->_data->window.close();
        }
        
        switch (event.type)
        {
            case sf::Event::KeyReleased:
                switch (event.key.code)
            {
                case sf::Keyboard::Up:
                    MainMenuState::MoveUp();
                    break;
                case sf::Keyboard::Down:
                    MainMenuState::MoveDown();
                    break;
                case sf::Keyboard::Return:
                    switch (MainMenuState::GetPressedItem())
                {
                    case 0:
                        std::cout << "Play button has been pressed" << std::endl;
                        this->_data->machine.AddState(StateRef(new GameState(_data)), true);

                        scenes::currentScene = scene::game; //edit: Antoni Tretiakov
                        this->_data->window.close(); //edit: Antoni Tretiakov

                        break;
                    case 1:
                        std::cout << "Options button has been pressed" << std::endl;
                        
                        break;
                    case 2:
                        std::cout << "Exit button has been pressed" << std::endl;

                        scenes::currentScene = scene::exit; //edit: Antoni Tretiakov
                        this->_data->window.close();
                        break;
                }
                    
                    
            }
                
        }
    
    }
}

void MainMenuState::Update(float dt)
{
    _animation.AnimationUpdate();
}

void MainMenuState::Draw(float dt)
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

void MainMenuState::MoveUp()
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

void MainMenuState::MoveDown()
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
