#include "scenes.h"

#include <Player.h>
#include <Animation.h>
#include <Music.h>
#include <EnemyControl.h>
#include <PlayerAnimation.h>
#include <FractalChart.h>
#include <Explosion.h>

//Obs³uga klawiatury
void control(Player* player, PlayerAnimation* ship)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player->Up = true;
        ship->Up = true;
    }
    else
    {
        player->Up = false;
        ship->Up = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player->Down = true;
        ship->Down = true;
    }
    else
    {
        player->Down = false;
        ship->Down = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player->Right = true;
        ship->Right = true;
    }
    else
    {
        player->Right = false;
        ship->Right = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player->Left = true;
        ship->Left = true;
    }
    else
    {
        player->Left = false;
        ship->Left = false;
    }
}

void scenes::game()
{
    sf::RenderWindow window{ {window_width, window_height}, "Window", sf::Style::Close}; //, sf::Style::Fullscreen
    sf::Event event;
    window.setFramerateLimit(60);

    // World

    World world;
    Music music;

    // Explosion
    Explosion exp;
    Explosion p_exp;

    FractalChart map("./Resources/Images/bgAnim.png", "./Resources/Images/bgStatic.png", sf::Vector2i(1280 * 4, 720 * 4), sf::Vector2i(1280, 720), 1);

    float timeStep = 1.f / 60.f;
    int32 velocityIterations = 3;
    int32 positionIterations = 1;
    // Player

    PlayerAnimation ship("./Resources/Images/player_ship.png", 44, 28, 4, 0.1f);
    Player player(&world, &ship, &map.m_fractal, 0, 0);

    // View
    sf::View view;
    view = window.getDefaultView();

    // Enemy
    EnemyControl enemyControl;
    Animation enemyShip("./Resources/Images/enemy_ship.png", 44, 28, 4, 0.1f);
    // Flags

    bool escapePressed = false;

    bool firstRun = true;
    for(int i = 0; i<10;i++)
        enemyControl.addEnemy(&world, &enemyShip, &map.m_fractal);
    while (window.isOpen() && scenes::currentScene == scene::game)
    {
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if (!escapePressed)
                {
                    scenes::currentScene = scene::pause;
                    scenes::pause(window);

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

        if (firstRun)
        {
            sf::Text text;
            sf::Font font;
            font.loadFromFile("./Resources/Fonts/pixel.ttf");
            text.setFont(font);
            text.setString(L"£adowanie...");
            text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
            text.setPosition(window_width/2, window_height/2);
            text.setFillColor(sf::Color::White);
            window.clear(sf::Color::Black);
            window.draw(text);
            window.display();

            map.update({ player.position.x * PPM, player.position.y * PPM });
            map.m_fractal.synchronize();

            firstRun = false;
        }

        //wykonanie jedneko kroku w symulacji

        world.m_world->Step(timeStep, velocityIterations, positionIterations);
        if (player.HP <= 0)
        {
            p_exp.update();
            p_exp.sprite.setPosition(sf::Vector2f(player.position.x * PPM, player.position.y * PPM));
            if (p_exp.amount == 27)
                scenes::currentScene = scene::menu;
        }
        exp.update();
        control(&player, &ship);
        set<Enemy*>::iterator i = enemyControl.forRemoval.begin();
        set<Enemy*>::iterator n = enemyControl.forRemoval.end();
        for (; i != n; ++i) {
            Enemy* dyingEnemy = *i;
        }

        enemyControl.forRemoval.clear();
        view.setCenter(player.position.x * PPM, player.position.y * PPM);
        map.update({ player.position.x * PPM, player.position.y * PPM });
        window.setView(view);
        player.HPUpdate(view.getCenter());
        player.playerUpdate(&ship, &map.m_fractal);
        window.clear();
        window.draw(map);
        window.draw(ship.sprite);
        window.draw(player.HPSpriteOutline);
        window.draw(player.HPSprite);
        enemyControl.update(&world, &player, &window, &enemyShip, &map.m_fractal, &exp);
        window.draw(exp.sprite);
        window.draw(p_exp.sprite);
        //Renederowanie klatki
        window.display();

        music.update();
    }

}