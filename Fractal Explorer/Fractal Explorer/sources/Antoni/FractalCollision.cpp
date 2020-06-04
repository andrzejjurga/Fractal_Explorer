#include <FractalCollision.h>

FractalCollision::FractalCollision()
{
	// none
}

FractalCollision::FractalCollision(FractalRenderer& fractal)
{
	m_fractal = &fractal;
}

void FractalCollision::setFractal(FractalRenderer& fractal)
{
	m_fractal = &fractal;
}

void FractalCollision::setPosition(sf::Vector2f &position)
{
	m_position = position;
}

sf::Vector2f FractalCollision::getPosition()
{
	return m_position;
}

void FractalCollision::move(sf::Vector2f offset)
{
	m_position += offset;
}

void FractalCollision::update()
{

	if (points.size() != m_pointsStatus.size())
	{
		m_pointsStatus.resize(points.size(),false);
	}

	size_t i = 0;

	for (auto status : m_pointsStatus)
	{
		status = m_fractal->belongsToSet( sf::Vector2md( *points.at(i) ));

		i++;
	}
}

bool FractalCollision::getPointStatus(size_t point)
{
	return m_pointsStatus.at(point);
}

FractalCollision::~FractalCollision()
{
	m_fractal = nullptr;
}