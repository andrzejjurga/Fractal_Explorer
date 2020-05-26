//26.05.2020
#include <World.h>
#include <Player.h>
#include <Animation.h>
#include <PlayerAnimation.h>
#include <FractalChart.h>
//#include <Enemy.h>

int main()
{
    sf::RenderWindow window{ {1280, 720}, "Window" }; //, sf::Style::Fullscreen
    sf::Event event;
    window.setFramerateLimit(60);

    // World

    World world;

    FractalChart map("./resources/bgAnim.png", "./resources/bgStatic.png",sf::Vector2i(1280*4,720*4), sf::Vector2i(1280,720),1);

    float timeStep = 1.f / 60.f;
    int32 velocityIterations = 3;
    int32 positionIterations = 1;

    // Player

    PlayerAnimation ship("./resources/player_ship.png", 140, 84, 4, 0.1f);
    Player player(&world, 0, 0);

    sf::View view;
    view = window.getDefaultView();

    // Enemy

    //PlayerAnimation enemyShip("./resources/enemy_ship.png", 140, 84, 4, 0.1f);
    //Enemy enemy(&world, 200, 400);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player.Up = true;
            ship.Up = true;
        }
        else
        {
            player.Up = false;
            ship.Up = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player.Down = true;
            ship.Down = true;
        }
        else
        {
            player.Down = false;
            ship.Down = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player.Right = true;
            ship.Right = true;
        }
        else
        {
            player.Right = false;
            ship.Right = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player.Left = true;
            ship.Left = true;
        }
        else
        {
            player.Left = false;
            ship.Left = false;
        }

        //wykonanie jedneko kroku w symulacji

        world.m_world->Step(timeStep, velocityIterations, positionIterations);

        view.setCenter(player.position.x * PPM, player.position.y * PPM);
        map.update({ player.position.x * PPM, player.position.y * PPM });
        window.setView(view);
        player.playerUpdate(&ship);

        window.clear();
        window.draw(map);
        window.draw(ship.sprite);
        window.display();
    }

}
