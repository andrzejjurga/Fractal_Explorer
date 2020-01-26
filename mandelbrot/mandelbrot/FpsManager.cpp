#include "FpsManager.h"

FpsManager::FpsManager(sf::String fontName, sf::Clock& c, int timeStep)
	:m_clock(c)
{
	m_timeStep = timeStep;
	m_font.loadFromFile(fontName);
	m_text.setFont(m_font);

	m_text.setFillColor(sf::Color::Green);
	m_text.setScale(0.5,0.5);
}

void FpsManager::calcFPS()
{
	int temp = m_clock.getElapsedTime().asMilliseconds();;

	if (temp != 0.f)
	{
		m_text.setString("FPS ~" + std::to_string(1000 / abs(temp) ) );
	}

}

bool FpsManager::clockTick()
{
	bool temp = m_clock.getElapsedTime().asMilliseconds() > m_timeStep;

	if (temp) m_clock.restart();

	return temp;
}

void FpsManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text, states);
}
