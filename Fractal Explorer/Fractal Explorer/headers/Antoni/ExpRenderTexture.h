#pragma once
#include <SFML/Graphics.hpp>

class ExpandedRenderTexture :public sf::RenderTexture
{
public:

	bool create(unsigned int width, unsigned int height, const sf::ContextSettings& settings = sf::ContextSettings());

	// Move the texture
	void move(float x, float y);
	void move(sf::Vector2f position);

private:

	sf::Texture m_tempTexture;
	sf::Sprite m_tempSprite;

};