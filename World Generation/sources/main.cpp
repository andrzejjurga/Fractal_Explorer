/////////////////////////////////////////////////////////////////////////////////
//
// Autor: Antoni Tretiakov
//
// Wersja: 0.8
// 
// Opis programu:
//      Program do generowanie Zbioru Mandelbrota na ekranie.
//
// Uwagi:
//      Muszê przetestowaæ, czy wydajniejsze bêdzie generowanie na karcie
//		graficznej. Nie wiem, czy to siê uda dlatego, ¿e niektóre karty
//		operuj¹ liczbami z przecinkiem o przybli¿eniu (float).
//		Dla du¿ych przybli¿eñ nie bêdzie mo¿na niczego wygenerowaæ
//		w takim przypadku.
//
// Wymagania:
//      SFML x86, SFML x64
//
/////////////////////////////////////////////////////////////////////////////////
//
// Obs³uga:
//      Escape     - Wyjœcie
//
/////////////////////////////////////////////////////////////////////////////////

#include "MandelViewer.h"
#include <SFML/Graphics.hpp>

constexpr auto window_width  = 1280;
constexpr auto window_height = 720;
constexpr auto optimization  = 1;

int main()
{
	/////////////////// Okno

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Mandelbrot");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	sf::Event windowEvent;

	//////////////////// Fraktal

	MandelViewer fractal;
	fractal.setWindow(window);

	// MandelViewer::create( trzy parametry )
	//		Parametr 1: rozmiar obrazka z fraktalem.
	//		Parametr 2: rozdzielczoœæ fraktala (Musi byæ mniejsza lub równa rozmiarowi z parametru 1)
	//		Parametr 3: optymalizacja (im wy¿sza wartoœæ, tym wiêcej w¹tków jest przeznaczona na generowanie)
	fractal.create(sf::Vector2i(window_width, window_height), sf::Vector2i(window_width / 4, window_height / 4), optimization);
	fractal.setScale(0.01);
	fractal.setPrecision(50);

	// MandelViewer::move( dwa parametry)
	//		Parametr 1: Wartoœæ o jak¹ przesuniemy siê na fraktalu
	//		Parametr 2:
	//			Je¿eli prawda, skaluje wartoœæ, ¿eby odpowiada³a przybli¿eniu.
	//			Je¿eli fa³sz, okreœla rzeczywiste przesuniêcie na uk³adzie wspó³rzêdnych (Fraktal znajduje siê w kole o promieniu 2 i œrodku (0,0) )
	fractal.move({ 1.5,0 }, false);

	sf::Clock timer;

	while (window.isOpen())
	{
		/////////////////// Eventy:

		while (window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed) window.close();

			if (windowEvent.type == sf::Event::KeyPressed)
				if (windowEvent.text.unicode == sf::Keyboard::Escape) window.close();
		}

		if (timer.getElapsedTime().asSeconds() > 0.1)
		{
			// MandelViewer::generate()
			// Uruchomienie w¹tków generuj¹cych obraz
			fractal.generate();

			// MandelViewer::synchronize()
			// Oczekiwanie na zakoñczenie pracy ka¿dego w¹tku.
			fractal.synchronize();

			// MandelViewer::update()
			// Zapisywanie zmian na teksturze.
			fractal.update();

			timer.restart();
		}

		/////////////////// Wyœwietlanie

		window.clear(sf::Color::Black);

		window.draw(fractal);

		window.display();
	}

	fractal.synchronize();

}