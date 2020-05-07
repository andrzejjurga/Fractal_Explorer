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
	string file = "ship.png";
	
	Animation ship(file, 232, 140, 4, 0.1f);
	

    World swiat;
    Player gracz(&swiat, 0.0f, 3.0f);


    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -11.0f);
    //kszta³t œciany
    b2PolygonShape groundBox;

    b2Body* groundBody = swiat.m_world->CreateBody(&groundBodyDef);


    // The extents are the half-widths of the box.
    groundBox.SetAsBox(100.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

   
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    sf::RectangleShape rectangle(sf::Vector2f(140, 100));
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

        // Now print the position and angle of the body.
        b2Vec2 position = gracz.body->GetPosition();
        float32 angle = gracz.body->GetAngle();

        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    
        ship.sprite.setPosition(100 * position.x, 300 * position.y);


        ship.AnimationUpdate();
		renderWindow.clear();
        renderWindow.draw(rectangle);
		renderWindow.draw(ship.sprite);
		renderWindow.display();
	}

	return 0;
}

