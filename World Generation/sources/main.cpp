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
//      Musz� przetestowa�, czy wydajniejsze b�dzie generowanie na karcie
//		graficznej. Nie wiem, czy to si� uda dlatego, �e niekt�re karty
//		operuj� liczbami z przecinkiem o przybli�eniu (float).
//		Dla du�ych przybli�e� nie b�dzie mo�na niczego wygenerowa�
//		w takim przypadku.
//
// Wymagania:
//      SFML x86, SFML x64
//
/////////////////////////////////////////////////////////////////////////////////
//
// Obs�uga:
//      Escape     - Wyj�cie
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
	//		Parametr 2: rozdzielczo�� fraktala (Musi by� mniejsza lub r�wna rozmiarowi z parametru 1)
	//		Parametr 3: optymalizacja (im wy�sza warto��, tym wi�cej w�tk�w jest przeznaczona na generowanie)
	fractal.create(sf::Vector2i(window_width, window_height), sf::Vector2i(window_width / 4, window_height / 4), optimization);
	fractal.setScale(0.01);
	fractal.setPrecision(50);

	// MandelViewer::move( dwa parametry)
	//		Parametr 1: Warto�� o jak� przesuniemy si� na fraktalu
	//		Parametr 2:
	//			Je�eli prawda, skaluje warto��, �eby odpowiada�a przybli�eniu.
	//			Je�eli fa�sz, okre�la rzeczywiste przesuni�cie na uk�adzie wsp�rz�dnych (Fraktal znajduje si� w kole o promieniu 2 i �rodku (0,0) )
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
			// Uruchomienie w�tk�w generuj�cych obraz
			fractal.generate();

			// MandelViewer::synchronize()
			// Oczekiwanie na zako�czenie pracy ka�dego w�tku.
			fractal.synchronize();

			// MandelViewer::update()
			// Zapisywanie zmian na teksturze.
			fractal.update();

			timer.restart();
		}

		/////////////////// Wy�wietlanie

		window.clear(sf::Color::Black);

		window.draw(fractal);

		window.display();
	}

	fractal.synchronize();

}