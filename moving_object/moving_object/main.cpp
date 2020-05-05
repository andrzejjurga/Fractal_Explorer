#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Animation.h"



int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(600, 480), "Testowanie animacji");
	sf::Event event;
	string file = "ship.png";
	
	Animation ship(file, 232, 140, 4, 0.1f);


	while (renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}

		ship.AnimationUpdate();
		renderWindow.clear();
		renderWindow.draw(ship.sprite);
		renderWindow.display();
	}

	return 0;
}