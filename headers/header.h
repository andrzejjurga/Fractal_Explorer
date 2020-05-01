#pragma once

// Nieistotny plik

// Header

/*

typedef std::vector<sf::Vector2f> ptVector;

float squared_distance(float x, float y)
{
	return x * x + y * y;
}

float distanceToClosestPoint(float x, float y, ptVector* points, float factor)
{
	int tempIndex=0;
	float tempDistance, pointDistance;
	for (int i = 1; i < points->size(); i++)
	{
		tempDistance  = squared_distance(x - points->at(tempIndex).x, y - points->at(tempIndex).y);
		pointDistance = squared_distance(x - points->at(i).x, y - points->at(i).y);

		if (pointDistance < tempDistance)
		{
			tempIndex = i;
		}
	}

	tempDistance = squared_distance(x - points->at(tempIndex).x, y - points->at(tempIndex).y);

	return tempDistance;
}

void testGridGenerator(sf::Image& image, ptVector &points, float factor)
{
	float smallestDistance;

	for (int iy = 0; iy < image.getSize().y; iy++)
	for (int ix = 0; ix < image.getSize().x; ix++)
	{
		smallestDistance = sqrt(distanceToClosestPoint(ix,iy,&points,factor));
		image.setPixel(ix, iy, sf::Color(smallestDistance, smallestDistance, smallestDistance));
	}
}

*/