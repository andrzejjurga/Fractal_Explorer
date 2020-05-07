#include "Menu.hpp"

Menu::Menu(float width, float height)
{
    font.loadFromFile(FONT_FILE_PATH);
    
    menu[0].setFont(font);
    menu[0].setCharacterSize(50);
    menu[0].setFillColor(sf::Color(50, 70, 170));
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
    
    menu[1].setFont(font);
    menu[1].setCharacterSize(50);
    menu[1].setFillColor(sf::Color(255, 255, 255));
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
    
    menu[2].setFont(font);
    menu[2].setCharacterSize(50);
    menu[2].setFillColor(sf::Color(255, 255, 255));
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
}

Menu::~Menu()
{
}

void Menu::Draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

