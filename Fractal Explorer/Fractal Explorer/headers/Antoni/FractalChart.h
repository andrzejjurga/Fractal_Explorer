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

namespace
{
	typedef unsigned int uInt;
	typedef unsigned short uShort;
	typedef const char* cCharP;

	constexpr uInt default_fractal_width  = 2560;
	constexpr uInt default_fractal_height = 1440;

	const     uInt default_opt_level = (uInt)sqrt(std::thread::hardware_concurrency());
}

class FractalChart : public sf::Drawable
{
public:

	FractalChart();

	FractalChart(string filePath, string filePath2, sf::Vector2i size, sf::Vector2i resolution, uShort optimization = default_opt_level);

	void update(sf::Vector2f position);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	Animation       m_background;
	Animation       m_background2;
	FractalRenderer m_fractal;
	sf::Vector2f    m_fractalPosition;
	sf::Vector2i    m_size;
	sf::Vector2i    m_resolution;
};
