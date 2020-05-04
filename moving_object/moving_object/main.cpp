#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>



int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(600, 480), "Testowanie animacji");
	sf::Event event;

	sf::Texture texture;
	texture.loadFromFile("ship.png");

	sf::IntRect rectSourceSprite(0, 0, 140, 232);
	sf::Sprite sprite(texture, sf::IntRect(0,0,140,232));
	sprite.setPosition(240, 124);
	sf::Clock clock;


	while (renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}

		if (clock.getElapsedTime().asSeconds() > 0.1f) {
			if (rectSourceSprite.left == 420)
				rectSourceSprite.left = 0;
			else
				rectSourceSprite.left += 140;
			sprite.setTextureRect(rectSourceSprite);
			clock.restart();
		}

		renderWindow.clear();
		renderWindow.draw(sprite);
		renderWindow.display();
	}

	return 0;
}