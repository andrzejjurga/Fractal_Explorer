#include "Menu.hpp"

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile(FONT_FILE_PATH))
    {
        //File didn't load
    }
    if (!texture.loadFromFile(BACKGROUND_FILE_PATH))
    {
        //File didn't load
    }
    
    sf::Vector2u size = texture.getSize();
    sprite.setTexture(texture);
    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    
    menu[0].setFont(font);
    menu[0].setCharacterSize(50);
    menu[0].setFillColor(sf::Color::Blue);//(50, 70, 170));
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width / 25, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
    
    menu[1].setFont(font);
    menu[1].setCharacterSize(50);
    menu[1].setFillColor(sf::Color::Red);//(255, 255, 255));
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(width / 25, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
    
    menu[2].setFont(font);
    menu[2].setCharacterSize(50);
    menu[2].setFillColor(sf::Color::Red);//(255, 255, 255));
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width / 25, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
    
    selectedItemIndex = 0;
    

}

Menu::~Menu()
{
}

void Menu::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}

void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}
