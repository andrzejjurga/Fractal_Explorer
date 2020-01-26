#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class FpsManager : public sf::Drawable
{
public:
	FpsManager(sf::String fontName, sf::Clock& c, int timeStep);
	void calcFPS();
	bool clockTick();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	int m_timeStep;

	sf::Clock& m_clock;
	sf::Font m_font;
	sf::Text m_text;

}; // FpsManager

