#pragma once

#define _USE_MATH_DEFINES

#include <SFML/System.hpp>
#include <math.h>

namespace mu
{
	// Percentage numbers

	double getPercOfNum(double percent, double number);

	// Distances

	double distance(sf::Vector2f pos1, sf::Vector2f pos2);

	double distance(double x, double y);

	double circleDistance(sf::Vector2f cir1, sf::Vector2f cir2, double r1, double r2);

	// Angles

	double angleBetween(sf::Vector2f point1, sf::Vector2f point2);

	double angleBetween(double x, double y);

	// Unit change

	double radToDeg(double radians);

	double degToRad(double degrees);
}