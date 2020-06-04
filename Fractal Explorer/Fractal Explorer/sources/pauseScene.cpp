#include "scenes.h"

void textInit(sf::Text& text, sf::Font& font, sf::Vector2f position = {0.f,0.f} );
void textInit(sf::Text& text, sf::Font& font, float x=0, float y=0);

void scenes::pause(sf::RenderWindow& window)
{

    window.setView(window.getDefaultView());

    sf::Font font;
    font.loadFromFile("./Resources/Fonts/pixel.ttf");

    sf::Text text;
    text.setString(L"~ Pauza ~");
    textInit(text, font, window_width * 0.5, window_height * 0.25);

    sf::Text text2;
    text2.setString(L"Czy na pewno chcesz wyjœæ");
    textInit(text2, font, window_width * 0.5, window_height * 0.5);

    sf::Text text2x1;
    text2x1.setString(L"do menu g³ównego?");
    textInit(text2x1, font, window_width * 0.5, window_height * 0.55);

    sf::Text text3;
    text3.setString(L"Tak");
    textInit(text3, font, window_width * 0.45, window_height * 0.65);

    sf::Text text4;
    text4.setString(L"Nie");
    textInit(text4, font, window_width * 0.55, window_height * 0.65);

    bool escapePressed = true;
    bool leftRightPressed  = false;

    bool wannaExit = false;

    // pause loop

    while (window.isOpen() && scenes::currentScene == scene::pause)
    {

        // event handling

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.text.unicode == sf::Keyboard::Enter)
            {
                if (wannaExit)
                {
                    scenes::currentScene = scene::menu;
                }
                else
                {
                    scenes::currentScene = scene::game;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if (!leftRightPressed)
                {
                    wannaExit = !wannaExit;
                    leftRightPressed = true;
                }
            }
            else { leftRightPressed = false; }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if (!escapePressed)
                {
                    scenes::currentScene = scene::game;
                    escapePressed = true;
                }
            }
            else { escapePressed = false; }

            if (event.type == sf::Event::EventType::Closed)
            {
                scenes::currentScene = scene::exit;
                window.close();
            }
        }

        // other
        if (wannaExit)
        {
            text3.setFillColor(sf::Color::Red);
            text4.setFillColor(sf::Color::White);
        }
        else
        {
            text3.setFillColor(sf::Color::White);
            text4.setFillColor(sf::Color::Red);
        }

        window.clear();

        window.draw(text);
        window.draw(text2);
        window.draw(text2x1);
        window.draw(text3);
        window.draw(text4);

        window.display();
    }
}

void textInit(sf::Text& text, sf::Font& font, sf::Vector2f position)
{
    text.setFont(font);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(position);
    text.setFillColor(sf::Color::White);
}

void textInit(sf::Text& text, sf::Font& font, float x, float y)
{
    text.setFont(font);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(x,y);
    text.setFillColor(sf::Color::White);
}