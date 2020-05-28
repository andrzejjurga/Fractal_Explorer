#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include "Animation.h"
#include "PlayerAnimation.h"
#include "Player.h"
#include "Enemy.h"
#include "World.h"
#include "b2GLDraw.h"
#include "Collision.h"



int main()
{
    //tworzenie okna
	sf::RenderWindow renderWindow(sf::VideoMode(1280, 720), "Testowanie fizyki");
    renderWindow.setFramerateLimit(60);
	sf::Event event;
	
    PlayerAnimation ship("player_ship.png", 44, 28, 4, 0.1f);
	Animation block("enemy_ship.png", 44, 28, 4, 0.1f);
    Animation block1("box.png", 44, 28, 4, 0.1f);
	
    World swiat;

    sf::View view;
    view = renderWindow.getDefaultView();

    Collision kolizje;


    //=============================================================
    b2GLDraw debugDrawInstance;
    swiat.m_world->SetDebugDraw(&debugDrawInstance);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //flags += b2Draw::e_jointBit;
    //flags += b2Draw::e_pairBit;
    //flags += b2Draw::e_aabbBit;
    //flags += b2Draw::e_centerOfMassBit;
    debugDrawInstance.SetFlags(flags);
    //=============================================================


    Player gracz(&swiat, &ship, 200.0f,400.0f);
    Enemy box(&swiat, &block, 100.0f, 100.0f);
    Enemy box1(&swiat, &block1, 400.0f, 300.0f);


    // Define the ground body.
    b2BodyDef groundBodyDef;
    //groundBodyDef.position.Set(1.f / swiat.PPM, 1.f / swiat.PPM);
    groundBodyDef.position.Set(15.f, 3.f);
    //kszta³t œciany
    b2PolygonShape groundBox;

    b2Body* groundBody = swiat.m_world->CreateBody(&groundBodyDef);


    // The extents are the half-widths of the box.
    groundBox.SetAsBox((1000.0f / PPM) /2, (100.0f / PPM)/2);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

   
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;




    // This is our little game loop.

	while (renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            gracz.Up = true;
            ship.Up = true;
        }
        else
        {
            gracz.Up = false;
            ship.Up = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            gracz.Down = true;
            ship.Down = true;
        }
        else
        {
            gracz.Down = false;
            ship.Down = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            gracz.Right = true;
            ship.Right = true;
        }
        else
        {
            gracz.Right = false;
            ship.Right = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            gracz.Left = true;
            ship.Left = true;
        }
        else
        {
            gracz.Left = false;
            ship.Left = false;
        }


        //wykonanie jedneko kroku w symulacji
        swiat.m_world->Step(timeStep, velocityIterations, positionIterations);
        //ustawienie kamery nad graczem
        view.setCenter(gracz.position.x * PPM, gracz.position.y * PPM);


        gracz.playerUpdate(&ship);
        box.enemyUpdate(&block, &gracz);
        box1.enemyUpdate(&block1, &gracz);
		renderWindow.clear();
		renderWindow.draw(ship.sprite);
		renderWindow.draw(block.sprite);
		renderWindow.draw(block1.sprite);

        swiat.m_world->DrawDebugData();
        renderWindow.setView(view);
		renderWindow.display();
        ship.sprite.setColor(sf::Color(255, 255, 255));
	}

	return 0;
}

