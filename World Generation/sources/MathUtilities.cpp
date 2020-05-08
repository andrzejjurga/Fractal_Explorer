#include "MathUtilities.h"

double mu::getPercOfNum(double percent, double number)
{
	return number * percent / 100.f;
}

double mu::distance(sf::Vector2f pos1, sf::Vector2f pos2)
{
	double x = ((double)pos2.x - (double)pos1.x), y = ((double)pos2.y - (double)pos1.y);
	return sqrt(x * x + y * y);
}

double mu::distance(double x, double y)
{
	return sqrt(x * x + y * y);
}

double mu::circleDistance(sf::Vector2f cir1, sf::Vector2f cir2, double r1, double r2)
{
	double x = ((double)cir2.x - (double)cir1.x), y = ((double)cir2.y - (double)cir1.y);
	return sqrt(x * x + y * y) - r1 - r2;
}

double mu::angleBetween(sf::Vector2f point1, sf::Vector2f point2)
{
	double angle = 0., x = ((double)point2.x - (double)point1.x), y = ((double)point2.y - (double)point1.y);
	if (x != 0.)
	{
		angle = atan(y / x);
		if (x < 0.) angle += M_PI;
	}
	else if (y > 0.) angle = M_PI_2;
	else angle = -M_PI_2;
	return angle;
}

double mu::angleBetween(double x, double y)
{
	double angle = 0.;
	if (x != 0.)
	{
		angle = atan(y / x);
		if (x < 0.) angle += M_PI;
	}
	else if (y > 0.) angle = M_PI_2;
	else angle = -M_PI_2;
	return angle;
}

double mu::radToDeg(double radians)
{
	return radians * 57.29577951; // radians * (180/PI)
}

double mu::degToRad(double degrees)
{
	return degrees * 0.01745329; // degrees * (PI/180)
}