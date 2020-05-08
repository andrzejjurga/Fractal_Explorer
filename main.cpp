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
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Up:
                            menu.MoveUp();
                            break;
                        case sf::Keyboard::Down:
                            menu.MoveDown();
                            break;
                        case sf::Keyboard::Return:
                            switch (menu.GetPressedItem())
                            {
                                case 0:
                                    std::cout << "Play button has been pressed" << std::endl;
                                    
                                    break;
                                case 1:
                                    std::cout << "Options button has been pressed" << std::endl;
                                    
                                    break;
                                case 2:
                                    std::cout << "Exit button has been pressed" << std::endl;
                                    window.close();
                                    break;
                            }
                            
                            
                    }
                    
                //case sf::Event::Closed:
                  //  window.close();
                    //break;

            }
        }
        
        window.clear();
        
        menu.Draw(window);
        
        window.display();
    }
}

