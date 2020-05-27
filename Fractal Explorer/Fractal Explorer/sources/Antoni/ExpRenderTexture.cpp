#include <ExpRenderTexture.h>

bool ExpandedRenderTexture::create(unsigned int width, unsigned int height, const sf::ContextSettings& settings)
{
	m_tempSprite.setPosition(0, 0);
	m_tempTexture.create(width, height);
	m_tempSprite.setTexture(m_tempTexture);
	m_tempSprite.setTextureRect(sf::IntRect(0,0,width,height));
	return this->sf::RenderTexture::create(width, height, settings);
}

void ExpandedRenderTexture::move(sf::Vector2f position)
{
	m_tempTexture = this->getTexture();
	m_tempSprite.setPosition(position);
	this->clear(sf::Color::Black);
	this->draw(m_tempSprite);
}

void ExpandedRenderTexture::move(float x, float y)
{
	m_tempTexture = this->getTexture();
	m_tempSprite.setPosition(x, y);
	this->clear(sf::Color::Black);
	this->draw(m_tempSprite);
}