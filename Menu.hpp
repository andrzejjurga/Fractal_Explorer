#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();
    
    void Draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() {return selectedItemIndex;}
    
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape start;
};

