#include <FractalChart.h>

FractalChart::FractalChart()
	:m_background("./resources/bgAnim.png", 720, 1280, 4, 0.2f),
	m_background2("./resources/bgStatic.png", 720, 1280, 2, 0.01f),
	m_size(1280, 720),
	m_resolution(1280, 720)
{
	m_background.sprite.setColor(sf::Color(128, 128, 128));
	m_fractal.create(sf::Vector2i(default_fractal_width, default_fractal_height), sf::Vector2i(default_fractal_width, default_fractal_height), default_opt_level);
	m_fractal.setPrecision(300);
}

FractalChart::FractalChart(string filePath,string filePath2, sf::Vector2i size, sf::Vector2i resolution, uShort optimization)
	:m_background(filePath, 720, 1280, 4, 0.2f),
	m_background2(filePath2, 720, 1280, 2, 0.01f),
	m_size(size),
	m_resolution(resolution)
{
	m_background.sprite.setColor(sf::Color(128, 128, 128));
	m_fractal.create(size, resolution, optimization);
	m_fractal.setPrecision(300);
}

void FractalChart::update(sf::Vector2f position)
{
	m_background.sprite.setPosition(position);
	m_background2.sprite.setPosition(position);

	if (m_fractal.isSynchronized())
	{

		m_fractal.update();
		m_fractal.setViewPosition(m_fractalPosition);

		m_fractalPosition.x = (int)position.x;
		m_fractalPosition.y = (int)position.y;

		m_fractal.setPosition(
			sf::Vector2md(
				-m_fractalPosition.x / (m_size.x / m_resolution.x),
				-m_fractalPosition.y / (m_size.y / m_resolution.y)
			),
			true
		);

		m_fractal.generate();
	}

	m_fractal.animateColor();

	m_background.AnimationUpdate({ 0,0 });
	m_background2.AnimationUpdate(sf::Vector2f(position.x * 0.75, position.y * 0.75));
}

void FractalChart::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite background3 = m_background2.sprite;
	background3.setTextureRect(
		sf::IntRect(
			background3.getTextureRect().left / 2,
			background3.getTextureRect().top / 2,
			background3.getTextureRect().width,
			background3.getTextureRect().height
			)
	);
	target.draw(m_background.sprite, states);
	target.draw(background3, states);
	target.draw(m_background2.sprite, states);
	target.draw(m_fractal);
}