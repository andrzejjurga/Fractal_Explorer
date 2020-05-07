#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Projekt!");
    
    Menu menu(window.getSize().x, window.getSize().y);
    
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        
        window.clear();
        
        menu.Draw(window);
        
        window.display();
    }
}

