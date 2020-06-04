#pragma once

////////////////////////////////////////////////////////////
//
// Klasa tworz¹ca Zbiór Mandelbrota z animowanym t³em.
//
// Antoni Tretiakov
//
////////////////////////////////////////////////////////////

#include <Animation.h>
#include <MandelViewer.h>
#include <thread>

namespace // global stuff
{

	typedef const char* cCharP;

	constexpr uint32_t default_fractal_width  = 2560;
	constexpr uint32_t default_fractal_height = 1440;

	const     uint32_t default_opt_level = (uint32_t)sqrt(std::thread::hardware_concurrency());
}

class FractalChart : public sf::Drawable
{
public:

	FractalChart();

	FractalChart(string filePath, string filePath2, sf::Vector2i size, sf::Vector2i resolution, uint16_t optimization = default_opt_level);

	void update(sf::Vector2f position);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


public:

	FractalRenderer m_fractal;

private:

	Animation       m_background;
	Animation       m_background2;
	sf::Sprite		m_background3;

	sf::Vector2f    m_fractalPosition;
	sf::Vector2i    m_size;
	sf::Vector2i    m_resolution;
};
