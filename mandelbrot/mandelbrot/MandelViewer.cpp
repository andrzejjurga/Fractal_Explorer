#include "MandelViewer.h"
#include <functional>
#include <iostream>

//Definitions


// Struct members.


void mdProperties::init(sf::Uint8 id, sf::IntRect r)
{
	thread_ID = id;
	rectangle = r;
	pixels = new sf::Uint8[1+rectangle.width * rectangle.height * 4];
}

void mdProperties::setPixel(sf::Uint16 x, sf::Uint16 y, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A=255)
{
	pixels[x * 4 + rectangle.width * 4 * y + 0] = R;
	pixels[x * 4 + rectangle.width * 4 * y + 1] = G;
	pixels[x * 4 + rectangle.width * 4 * y + 2] = B;
	pixels[x * 4 + rectangle.width * 4 * y + 3] = A;
}

void mdAlgorithm(MandelViewer* object, sf::Uint8 thread_ID)
{
	object->m_mutex.lock();
	mdType scale = object->m_scale;
	mdType precision = object->m_precision;
	sf::Vector2md center = object->m_centerPoint;
	sf::Vector2md displacement = object->m_displacement;
	object->m_mutex.unlock();

	mdProperties *ptr = &object->m_threadAtb[thread_ID];
	std::complex<mdType>* z = ptr->z;
	size_t iteration;

	for(mdType y = 0; int(y) < ptr->rectangle.height; y++)
	for(mdType x = 0; int(x) < ptr->rectangle.width; x++)
	{
		iteration = 0;
		z[0] = { 0,0 };
		z[1] = {
			scale * (ptr->rectangle.left + x - center.x) - displacement.x,
			scale * (ptr->rectangle.top + y - center.y) - displacement.y
		};

		while (abs(z[0]) < 2.0 && iteration++ < precision)
			z[0] = z[0] * z[0] + z[1];
		ptr->setPixel(x, y,
			128 + 127 * sin(iteration / 14.0),
			128 + 127 * sin(iteration / 15.0),
			128 + 127 * sin(iteration / 16.0)
		);
	}

	object->m_mutex.lock();

	object->m_texture.update(
		ptr->pixels,
		ptr->rectangle.width, ptr->rectangle.height,
		ptr->rectangle.left, ptr->rectangle.top
	);

	object->m_mutex.unlock();
}


// Class members..


MandelViewer::MandelViewer()
{
	// Empty
}

MandelViewer::~MandelViewer()
{

}

MandelViewer::MandelViewer(sf::Vector2i size, sf::Uint8 optimalisation_level = 1)
{
	m_precision = 50;
	m_size = size;
	m_centerPoint = sf::Vector2md(size.x / 2.0, size.y / 2.0);
	m_scale = 0.05;
	if (optimalisation_level < 1 || optimalisation_level > 7) optimalisation_level = 2;
	m_threads_Ammount = pow(optimalisation_level, 2);
	m_texture.create(m_size.x, m_size.y);
	m_sprite.setTexture(m_texture);
	//m_sprite.scale(4, 4);

	m_threadAtb = new mdProperties[m_threads_Ammount];

	m_threads = new sf::Thread * [m_threads_Ammount];
	for (size_t i = 0; i < m_threads_Ammount; i++)
	{
		m_threads[i] = new sf::Thread(std::bind(&mdAlgorithm, this, i));
	}

	sf::IntRect rectangle;
	rectangle.width = m_size.x / sqrt(m_threads_Ammount);
	rectangle.height = m_size.y / sqrt(m_threads_Ammount);

	sf::Uint8 temp = 0;
	for (size_t i = 0; i < sqrt(m_threads_Ammount); i++)
	for (size_t j = 0; j < sqrt(m_threads_Ammount); j++, temp++)
	{
		rectangle.left = static_cast<size_t>(i * rectangle.width);
		rectangle.top = static_cast<size_t>(j * rectangle.height);
		m_threadAtb[temp].init(temp, rectangle);
	}
}

void MandelViewer::create(sf::Vector2i size, sf::Uint8 optimalisation_level = 1)
{
	m_precision = 50;
	m_size = size;
	m_centerPoint = sf::Vector2md(size.x / 2.0, size.y / 2.0);
	m_scale = 0.05;
	if (optimalisation_level < 1 || optimalisation_level > 7) optimalisation_level = 2;
	m_threads_Ammount = pow(optimalisation_level, 2);
	m_texture.create(m_size.x, m_size.y);
	m_sprite.setTexture(m_texture);
	//m_sprite.scale(4, 4);

	m_threadAtb = new mdProperties[m_threads_Ammount];

	m_threads = new sf::Thread * [m_threads_Ammount];
	for (size_t i = 0; i < m_threads_Ammount; i++)
	{
		m_threads[i] = new sf::Thread(std::bind(&mdAlgorithm, this, i));
	}

	sf::IntRect rectangle;
	rectangle.width = m_size.x / sqrt(m_threads_Ammount);
	rectangle.height = m_size.y / sqrt(m_threads_Ammount);

	sf::Uint8 temp = 0;
	for (size_t i = 0; i < sqrt(m_threads_Ammount); i++)
	for (size_t j = 0; j < sqrt(m_threads_Ammount); j++, temp++)
	{
		rectangle.left = static_cast<size_t>(i * rectangle.width);
		rectangle.top = static_cast<size_t>(j * rectangle.height);
		m_threadAtb[temp].init(temp, rectangle);
	}
}

void MandelViewer::generate()
{
	for (size_t i = 0; i < m_threads_Ammount; i++)
	{
		m_threads[i]->launch();
	}
}

void MandelViewer::synchronize()
{
	for (size_t i = 0; i < m_threads_Ammount; i++)
	{
		m_threads[i]->wait();
	}
}

void MandelViewer::setPrecision(sf::Uint16 precision)
{
	m_precision = precision;
}

void MandelViewer::precise(sf::Uint16 precision)
{
	m_precision += precision;
}

void MandelViewer::setScale(mdType scale)
{
	m_scale = scale;
}

void MandelViewer::scale(mdType scale)
{
	m_scale *= scale;
}

void MandelViewer::imageScale(float x, float y)
{
	m_sprite.scale(x, y);
}

void MandelViewer::setImageScale(float x, float y)
{
	m_sprite.setScale(x, y);
}

void MandelViewer::setPosition(sf::Vector2md position)
{
	m_displacement = position;
}

void MandelViewer::move(sf::Vector2md vector, bool scale = false)
{
	if (scale)
	{
		m_displacement += sf::Vector2md(vector.x * m_scale, vector.y * m_scale);
	}
	else m_displacement += vector;

}

void MandelViewer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
