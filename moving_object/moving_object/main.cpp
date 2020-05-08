#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Animation.h"
#include "Player.h"
#include "World.h"


int main()
{
    //tworzenie okna
	sf::RenderWindow renderWindow(sf::VideoMode(1440, 720), "Testowanie animacji");
    renderWindow.setFramerateLimit(60);
	sf::Event event;
	
	Animation ship("ship.png", 140, 84, 4, 0.1f);
	Animation block("block.png", 100, 100, 4, 0.1f);
	Animation block1("block1.png", 100, 100, 4, 0.1f);
	
    World swiat;

    Player gracz(&swiat, 400.0f, 500.0f);
    Player box(&swiat, 1.0f, 300.0f);
    Player box1(&swiat, 100.0f, 300.0f);


    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);
    //kszta³t œciany
    b2PolygonShape groundBox;

    b2Body* groundBody = swiat.m_world->CreateBody(&groundBodyDef);


    // The extents are the half-widths of the box.
    groundBox.SetAsBox((1000.0f / swiat.PPM) /2, (100.0f / swiat.PPM)/2);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

   
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    sf::RectangleShape rectangle(sf::Vector2f(1440, 100));
    rectangle.setFillColor(sf::Color(100, 250, 50));
    rectangle.setPosition(0, 0);


    // This is our little game loop.

	while (renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}



        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        swiat.m_world->Step(timeStep, velocityIterations, positionIterations);

        //printf("%4.2f %4.2f %4.2f\n", position.x / swiat->PPM, position.y / swiat.PPM, angle);


        gracz.playerUpdate(&ship);
        box.playerUpdate(&block);
        box1.playerUpdate(&block1);
		renderWindow.clear();
        renderWindow.draw(rectangle);
		renderWindow.draw(ship.sprite);
		renderWindow.draw(block.sprite);
		renderWindow.draw(block1.sprite);
		renderWindow.display();
	}

	return 0;
}

