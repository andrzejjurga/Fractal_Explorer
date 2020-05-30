//26.05.2020
#include <World.h>
#include <Player.h>
#include <Animation.h>
#include <PlayerAnimation.h>
#include <FractalChart.h>
#include <Enemy.h>
#include <Music.h>
#include <EnemyControl.h>

int main()
{
    sf::RenderWindow window{ {1280, 720}, "Window" }; //, sf::Style::Fullscreen
    sf::Event event;
    window.setFramerateLimit(60);


    // World

    World world;

    Music music;

    FractalChart map("./resources/bgAnim.png", "./resources/bgStatic.png",sf::Vector2i(1280*4,720*4), sf::Vector2i(1280,720),1);

    float timeStep = 1.f / 60.f;
    int32 velocityIterations = 3;
    int32 positionIterations = 1;

    // Player

    //PlayerAnimation ship("./resources/explosion.png", 350, 350, 28, 0.1f);
    PlayerAnimation ship("./resources/player_ship.png", 44, 28, 4, 0.1f);
    Animation enemyShip("./resources/enemy_ship.png", 44, 28, 4, 0.1f);
    Player player(&world, &ship, 0, 0);

    sf::View view;
    view = window.getDefaultView();


    // Enemy
    EnemyControl enemyControl;
   // Animation enemyShip("./resources/enemy_ship.png", 44, 28, 4, 0.1f);
   // Enemy enemy(&world, &enemyShip, 200, 400);

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
            enemyControl.addEnemy(&world, &enemyShip);
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

        //wykonanie jednego kroku w symulacji

        world.m_world->Step(timeStep, velocityIterations, positionIterations);
        player.HPUpdate(view.getCenter());
        window.setView(view);
        view.setCenter(player.position.x * PPM, player.position.y * PPM);

        map.update({ player.position.x * PPM, player.position.y * PPM });
        player.playerUpdate(&ship);
        //enemy.enemyUpdate(&enemyShip, &player);

        window.clear();
        window.draw(map);
        window.draw(ship.sprite);
        window.draw(player.HPSpriteOutline);
        window.draw(player.HPSprite);
        //window.draw(enemyShip.sprite);
        enemyControl.update(&world, &player, &window, &enemyShip);
        window.display();
        music.update();
    }
}
