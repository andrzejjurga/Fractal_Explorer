#pragma once

#include <SFML/Graphics.hpp>

class Velocity :public sf::Drawable
{
public:

    Velocity() :m_line(), m_angle(0.0), m_length(10.0)
    {
        m_line.setPrimitiveType(sf::PrimitiveType::Lines);
        m_line.resize(2);
        m_line[0].color = sf::Color::Red;
        m_line[1].color = sf::Color::Red;
    }

    Velocity(double angle, double length) :m_line(), m_angle(angle), m_length(length)
    {
        m_line.setPrimitiveType(sf::PrimitiveType::Lines);
        m_line.resize(2);
        m_line[0].color = sf::Color::Red;
        m_line[1].color = sf::Color::Red;
    }

    void setPosition(sf::Vector2f position) { m_line[0].position = position; this->update(); }
    void setAngle(double angle) { m_angle = angle; this->update(); }
    void setLength(double length) { m_length = length; this->update(); }
    void setColor(sf::Color color) { m_line[0].color = color; m_line[1].color = color; }

    void update()
    {
        m_line[1].position = sf::Vector2f(m_line[0].position.x + m_length * cos(m_angle), m_line[0].position.y + m_length * sin(m_angle));
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_line, states);
    }

private:

    sf::VertexArray m_line;
    double m_angle;
    double m_length;
};