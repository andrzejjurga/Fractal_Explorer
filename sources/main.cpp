/////////////////////////////////////////////////////////////////////////////////
//
// Autor: Antoni Tretiakov
//
// Wersja: 0.5
// 
// Opis programu:
//      Program do wykrywania kolizji miêdzy okr¹g³ym obiektem
//      i nierówn¹ powierzchni¹ na obrazie.
//
// Uwagi:
//      Bardzo prawdopodobne jest, ¿e przysz³e wersje programu
//      bêd¹ dzia³a³y na innej zasadzie, to znaczy zmianê
//      dotychczasowego algorytmu.
//
//      Program jest ma³o schludnie napisany!
//
// Wymagania:
//      SFML x86, FastNoise
//
/////////////////////////////////////////////////////////////////////////////////
//
// Obs³uga:
//
//      góra, dó³  - (Strza³ki) przybli¿anie, oddalanie
//
//      W, A, S, D - kierowanie obiektem
//
//      1, 2       - Przyœpieszanie, spowalnianie klatek
//
//      Escape     - Wyjœcie
//
/////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <testTexture1.h>
#include <Velocity.h>

using namespace std;

int main()
{

    sf::RenderWindow window{ {1280, 720}, "Window"};
    window.setFramerateLimit(60);
    sf::View view;
    view = window.getDefaultView();
    view.setSize(640, 360);

    // Graphics

    sf::Image image;
    image.create(640, 360);
    sf::Texture texture;
    sf::Sprite sprite;

    game::generateLvl(image, { 0,0 }, 1, 1, 1);
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    sf::Clock c;
    sf::Clock regenerate;
    sf::Vector2f velocity;
    sf::Vector2f lastPosition;
    sf::Vector2f colision;
    sf::Vector2f col;

    sf::CircleShape player;
    player.setRadius(15.f);
    player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
    player.setFillColor(sf::Color(255, 255, 255, 128));

    // Main loop
    
    float drought = 0;
    double zoom = 0.008;
    int seed = 0;
    float timeStep = 0.03;
    bool a = false;

    float maxVel = 20;

    float lvldisplacement = 5;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.text.unicode == sf::Keyboard::Escape) window.close();
        }

        window.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) timeStep = 0.03f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) timeStep = 1.f;

        

        if (regenerate.getElapsedTime().asSeconds() > timeStep)
        {
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x > -maxVel ? velocity.x -= 0.5 : -maxVel;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))  velocity.x < maxVel  ? velocity.x += 0.5 : maxVel;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))  velocity.y > -maxVel ? velocity.y -= 0.5 : -maxVel;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))  velocity.y < maxVel  ? velocity.y += 0.5 : maxVel;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))   zoom > 0.0008 ? zoom -= 0.0001 : 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) zoom < 0.016  ? zoom += 0.0001 : 0;

            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) seed ++;
            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) seed --;

            regenerate.restart();

            if (col.x == 0 && col.y == 0)
            {
                lastPosition = player.getPosition();
            }
            else
            {
                velocity.x = col.x;
                velocity.y = col.y;
            }

            if (a)
            {
                player.setPosition(lastPosition);
                a = false;
            }

            player.move(velocity);

            velocity.x *= 0.95;
            velocity.y *= 0.95;

            game::generateLvl(image, player.getPosition() + sf::Vector2f(lvldisplacement,0), seed, drought, zoom);

            col = game::checkCollision(image, player, velocity, zoom, a, window);

            sprite.setPosition(player.getPosition());
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            
        }

        Velocity vv;
        vv.setAngle(game::calcAngle(velocity.x,velocity.y));
        vv.setLength(10*game::distance({0.0,0.0}, velocity));
        vv.setPosition(player.getPosition());

        Velocity cc;
        cc.setAngle(game::calcAngle(col.x, col.y));
        cc.setLength(10 * game::distance({ 0,0 }, col));
        cc.setPosition(player.getPosition());
        cc.setColor(sf::Color::Blue);
        

        view.setCenter(player.getPosition());
        window.setView(view);

        
        window.draw(sprite);
        window.draw(player);
        window.draw(vv);
        window.draw(cc);
        window.display();
    }
}
