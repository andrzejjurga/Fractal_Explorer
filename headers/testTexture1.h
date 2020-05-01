#pragma once

#include <FastNoise.h>
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include<math.h>

namespace game
{

	// Funkcja do sprawdzenia czy liczba 'a' jest miêdzy liczbami 'b' i 'c'

	bool in(double a, double b, double c)
	{
		return (a >= b && a <= c);
	}

	// Funkcje do sprawdzania odleg³oœci

	double squareDistance(double x1, double y1, double x2, double y2)
	{
		return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	}

	double distance(double x, double y, double x1, double y1)
	{
		return sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
	}

	double distance(sf::Vector2f A, sf::Vector2f B)
	{
		double x = A.x, x1 = B.x, y = A.y, y1 = B.y;
		return sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
	}

	// Funkcje do obliczania k¹ta

	double calcAngle(double x, double y)
	{
		double angle = 0.f;
		if (x != 0.0)
		{
			angle = atan(y / x);
			if (x < 0.0) angle += M_PI;
		}
		else
		{
			if (y > 0.0) angle = M_PI_2;
			else		 angle = -M_PI_2;
		}
		return angle;
	}

	double calcAngle(sf::Vector2f A, sf::Vector2f B)
	{
		double angle = 0.0, x = B.x - A.x, y = B.y - A.y;
		if (x != 0.0)
		{
			angle = atan(y / x);
			if (x < 0.0) angle += M_PI;
		}
		else
		{
			if (y > 0.0) angle = M_PI_2;
			else		 angle = -M_PI_2;
		}
		return angle;
	}

	// Algorytm marszu wzd³u¿ promienia "ray marching" (Na razie nieu¿yty)

	float rayMarcher(sf::Vector2f p0, double pRadius, sf::Vector2f velocity, sf::Vector2f obstacle, double oRadius, sf::RenderWindow& window)
	{
		double		dist = 0.0;
		double		pdist = 0.0;
		const double velLength = hypot(velocity.x, velocity.y);
		const double velAngleX = cos(calcAngle(velocity.x, velocity.y));
		const double velAngleY = sin(calcAngle(velocity.x, velocity.y));

		sf::Vector2f p;
		sf::CircleShape c;
		c.setFillColor(sf::Color::Transparent);
		c.setOutlineThickness(2);
		c.setOutlineColor(sf::Color::Red);
		sf::Vertex verts[2];
		verts[0].position = p0;
		verts[0].color = sf::Color::Green;
		verts[1].color = sf::Color::Green;

		for (int i = 0; i < 20; i++)
		{
			p = sf::Vector2f(p0.x + dist * velAngleX, p0.y + dist * velAngleY);
			pdist = distance(p, obstacle) - pRadius - oRadius;
			dist += pdist;
			c.setRadius(pdist);
			c.setPosition(p);
			c.setOrigin(c.getGlobalBounds().width / 2.0, c.getGlobalBounds().height / 2.0);
			window.draw(c);

			if (pdist < 2 || pdist > velLength) break;
		}
		verts[1].position = p;
		window.draw(verts, 2, sf::Lines);
		return dist;
	}

	// Proceduralne generowanie mapy wysokoœciowej.
	// Opisy s¹ po angielsku, dlatego ¿e to funkcja z mojego innego programu.

	void generateLvl(sf::Image& image, sf::Vector2f offset, int seed, float time, double freq = 0.008f)
	{
		// noise generator setup.
		FastNoise noise;
		noise.SetSeed(seed);
		noise.SetNoiseType(FastNoise::NoiseType::PerlinFractal);
		noise.SetFrequency(freq);
		noise.SetInterp(FastNoise::Interp::Quintic);

		noise.SetFractalType(FastNoise::FractalType::FBM);
		noise.SetFractalLacunarity( 2.5 );
		noise.SetFractalGain(0.45 );
		noise.SetFractalOctaves(5);

		double water_level = 115 + 15 * cos( static_cast<double>(seed) * 11.0 ); // 100 - 130
		double sand_level = 138 - 5 * sin( static_cast<double>(seed) * 7.0 ); // 133 - 143
		double grass_level = 170 - 10 * cos(static_cast<double>(seed) * 1.5); // 160 - 180
		double mountain_level = 190;
		double mountain_snow_level = 255;

		// For each pixel in the image:
		for (unsigned int y = 0; y < image.getSize().y; y++)
		for (unsigned int x = 0; x < image.getSize().x; x++)
		{
			// Generate one pixel of unfiltered noise. Returned value oscillates between -1 and 1.
			float tempNoise = noise.GetNoise(x + offset.x * (0.008f / freq) - image.getSize().x/2.0, y+offset.y * (0.008f / freq) - image.getSize().y / 2.0);

			// Cast the noise to a value between 0 and 255 so it can be the color intensity.
			sf::Uint8 color = static_cast<sf::Uint8>(128+127*tempNoise);

			sf::Uint8 r = in(color, water_level, sand_level) ? color * 1.6 : in(color, grass_level, mountain_level) ? 255 - color : in(color, mountain_level, mountain_snow_level) ? color : 0;
			sf::Uint8 g = in(color, water_level, sand_level) ? color * 1.6 : in(color, sand_level, mountain_level)  ? 255 - color : in(color, mountain_level, mountain_snow_level) ? color : 0;
			sf::Uint8 b = in(color, 0, water_level )         ? 255-color   : in(color, grass_level, mountain_level) ? 255 - color : in(color, mountain_level, mountain_snow_level) ? color : 0;

			// Put only mountain or snow pixel (for test purposes) on the image.
			if (color < grass_level) { r = 1; g = 2; b = 3; }
			image.setPixel(x, y, sf::Color(r,g,b) );
		}
	}

	// Wykrywanie kolizji z nieregularnym obiektem na obrazie.

	sf::Vector2f checkCollision(sf::Image& image, sf::CircleShape& player, sf::Vector2f& vel, float zoom, bool& a, sf::RenderWindow& window)
	{
		sf::Color color;
		double radius = player.getRadius();
		sf::Vector2u center = sf::Vector2u(image.getSize().x / 2, image.getSize().y / 2);
		sf::Vector2<double> translatedPos;
		sf::Vector2<double> minPoint;
		double scale = (0.01 / zoom);
		double distance;
		double mindistance = radius * radius;
		bool collision_detected = false;

		for (int x = 0; x < radius * 2; x++)
			for (int y = 0; y < radius * 2; y++)
			{
				translatedPos.x = center.x - radius + x;
				translatedPos.y = center.y - radius + y;
				color = image.getPixel(translatedPos.x + vel.x, translatedPos.y + vel.y);

				if (color.r == color.g && color.r == color.b)
				{
					distance = game::squareDistance(center.x, center.y, translatedPos.x, translatedPos.y);
					if (distance < 1) { a = true; x = radius * 2; y = x; }
					if (distance < mindistance)
					{
						collision_detected = true;
						mindistance = distance;
						minPoint = translatedPos;
						image.setPixel(center.x + x - radius + vel.x, center.y + y - radius + vel.y, sf::Color::Green);
					}
				}
			}

		if (collision_detected)
		{

			mindistance = sqrt(mindistance);
			double velLen = game::distance({ 0.0,0.0 }, vel);

			double alpha;
			double beta = game::calcAngle(vel.x, vel.y);
			double gamma = game::calcAngle(center.x - minPoint.x, center.y - minPoint.y);
			alpha = gamma - beta;

			double amplitude = (radius - mindistance) / scale;

			return sf::Vector2f(
				amplitude * cos(gamma),
				amplitude * sin(gamma)
			);

		}
		return { 0, 0 };
	}

}
