#pragma once

// wykrywanie kolizji z fraktalem //


#include <vector>
#include <MandelViewer.h>

/// \brief Checks collision with a fractal (nothing more).
class FractalCollision
{

public:


	FractalCollision();
	FractalCollision(FractalRenderer& fractal);

	void setFractal(FractalRenderer& fractal);

	void setPosition(sf::Vector2f& position);
	sf::Vector2f getPosition();

	void move(sf::Vector2f offset);

	void update();

	bool getPointStatus(size_t point);

	~FractalCollision();


	std::vector<sf::Vector2f*> points;

	FractalRenderer* m_fractal;

private:

	sf::Vector2f m_position;
	std::vector<bool> m_pointsStatus;

};