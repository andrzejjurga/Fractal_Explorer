#pragma once

#include <SFML/Graphics.hpp>

constexpr uint32_t window_width = 1280;
constexpr uint32_t window_height = 720;

enum class scene
{
	menu = 0,
	game = 1,
	pause = 2,
	exit = 3
};

namespace scenes
{

	extern scene currentScene;

	void menu();
	void game();
	void pause(sf::RenderWindow& window);

}