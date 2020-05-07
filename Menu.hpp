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
    
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

