#include "..\MandelViewer.h"
#include "../FpsManager.h"
#include <SFML/Graphics.hpp>

bool isPressed(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key)) return true;
	else return false;
}

int main()
{
	// Window
	sf::Clock windowClock;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Mandelbrot", sf::Style::Default);
	sf::Event windowEvent;
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	// Fractal

	MandelViewer fractal;
	fractal.create(sf::Vector2i(1280/4, 720/4), 6);
	fractal.setPrecision(500);
	fractal.setImageScale(4,4);
	bool generate = true;

	// FPS

	FpsManager fps("fonts/Ubuntu-Regular.ttf",windowClock, 16);

	// Main loop

	while (window.isOpen())
	{
		// Event handling

		while (window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed) window.close();
		}

		// On clock tick

		fps.calcFPS();
		if (fps.clockTick())
		{

			if (generate)
			{
				fractal.generate();
				fractal.synchronize();
				generate = false;
			}

			if (isPressed(sf::Keyboard::Left))
			{
				fractal.move(sf::Vector2md(5.0, 0.0), true);
				generate = true;
			}
			if(isPressed(sf::Keyboard::Right))
			{
				fractal.move(sf::Vector2md(-5.0, 0.0), true);
				generate = true;
			}
			if(isPressed(sf::Keyboard::Up))
			{
				fractal.move(sf::Vector2md(0.0, 5.0), true);
				generate = true;
			}
			if(isPressed(sf::Keyboard::Down))
			{
				fractal.move(sf::Vector2md(0.0, -5.0), true);
				generate = true;
			}
			if (isPressed(sf::Keyboard::W))
			{
				fractal.scale(0.95);
				generate = true;
			}
			if (isPressed(sf::Keyboard::S))
			{
				fractal.scale(1.05);
				generate = true;
			}
		} // fps.clockTick();

		// Displaying

		window.clear(sf::Color::Black);

		window.draw(fractal);
		window.draw(fps);

		window.display();
	}

} // Main