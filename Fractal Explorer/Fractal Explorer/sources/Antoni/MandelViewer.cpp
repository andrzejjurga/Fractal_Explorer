#include "MandelViewer.h"
#include <functional>

// Friend struct members.

mdProperties::mdProperties()
	:isWorking(false),
	object(nullptr),
	thread_ID(-1)
{

}

void mdProperties::init(sf::Uint8 id, sf::IntRect r)
{
	isWorking = false;
	thread_ID = id;
	rectangle = r;
	image.create(rectangle.width, rectangle.height);
}

bool mdProperties::isActive()
{
	object->m_mutex.lock();
	bool result = this->isWorking;
	object->m_mutex.unlock();
	return result;
}

// Friend functions

void mdAlgorithm(FractalRenderer* object, sf::Uint8 thread_ID)
{
	// Safely copying all that is needed with locking the thread.
	object->m_mutex.lock();

		object->m_threadAtb[thread_ID].isWorking = true;
		mdType        scale          = object->m_scale;
		mdType        precision      = object->m_precision;
		sf::Vector2md center         = object->m_centerPoint;
		sf::Vector2md relativeCenter = object->m_relativeCenter;
		sf::Vector2md displacement   = object->m_displacement;
		sf::IntRect   rectangle      = object->m_threadAtb[thread_ID].rectangle;
		mdProperties* ptr            =&object->m_threadAtb[thread_ID];

	object->m_mutex.unlock();

	// Defining variables.

	complex z, c;
	size_t iteration;
	mdType tempRe;

	// This is similiar to a shader, but on a processor...
	// The code beneath defines where the fractal should be.

	for (mdType y = 0; y < rectangle.height; y++)
	{
		for(mdType x = 0; x < rectangle.width; x++)
		{
			iteration = 0;
			z = { 0, 0};
			c = {
				scale * (rectangle.left + x - center.x) - displacement.x - relativeCenter.x,
				scale * (rectangle.top  + y - center.y) - displacement.y - relativeCenter.y
			};

			while (z.Im * z.Im + z.Re * z.Re < 4.0 && ++iteration < precision)
			{
				tempRe = (z.Re * z.Re - z.Im * z.Im) + c.Re;
				z.Im   = (2.0 * z.Re * z.Im) + c.Im;
				z.Re   = tempRe;
			}

			double number = (z.Re * z.Re + z.Im * z.Im) * c.Re - (2.0 * z.Re * z.Im) * c.Im;

			if (iteration == precision)
				ptr->image.setPixel( (unsigned int)x, (unsigned int)y, sf::Color(50 + 20 * cos(100 * number),0, 50 + 20 * sin(100 * number)));
			else
				ptr->image.setPixel(
					(unsigned int)x,
					(unsigned int)y,
					sf::Color(
						(sf::Uint8)(155 + 100 * sin(-0.5 + iteration / 51.0)),
						(sf::Uint8)(155 + 100 * sin( 1.5 + iteration / 58.0)),
						(sf::Uint8)(155 + 100 * sin( 1.5 + iteration / 53.0)),
						160
					)
				);
		}

	}

	object->m_mutex.lock();

	object->m_texture.update(ptr->image,ptr->rectangle.left,ptr->rectangle.top);

	object->m_threadAtb[thread_ID].isWorking = false;

	object->m_mutex.unlock();
}


// Class members..


FractalRenderer::FractalRenderer()
	:m_precision(350),
	//Scale = 8.80861e-09, position = (0.740612, 0.112612)
	m_relativeCenter(0.740612, 0.112612),
	m_scale(2e-08),//8.5e-09
	m_threads_Ammount(0),
	m_threadAtb(nullptr),
	m_threads(nullptr)
{
	m_texture.setSmooth(true);
}

FractalRenderer::~FractalRenderer()
{
	this->clear();
}

void FractalRenderer::create(sf::Vector2i size, sf::Vector2i resolution, sf::Uint8 optimalisation_level = 1)
{
	if (m_threads_Ammount > 0)
	{
		this->clear();
		m_scale = m_scale * static_cast<mdType>(m_resolution.x) / static_cast<mdType>(resolution.x);
	}

	m_size = size;
	m_resolution = resolution;
	m_centerPoint = sf::Vector2md(m_resolution.x / 2.0, m_resolution.y / 2.0);

	m_renderTexture.create(m_size.x, m_size.y);
	m_renderTexture.draw(m_sprite);
	m_renderTexture.display();

	m_renderSprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
	m_renderSprite.setTexture(m_renderTexture.getTexture());
	m_renderSprite.setOrigin(m_renderSprite.getGlobalBounds().width / 2.0, m_renderSprite.getGlobalBounds().height / 2.0);
	m_renderSprite.setPosition((float)m_size.x/2, (float)m_size.y/2);

	m_texture.create(m_resolution.x, m_resolution.y);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_resolution.x, m_resolution.y));
	m_sprite.setScale((float)(m_size.x / m_resolution.x), (float)(m_size.y / m_resolution.y));


	// Thread stuff

	if (optimalisation_level < 1 || optimalisation_level > 7) optimalisation_level = 1;
	m_threads_Ammount = (sf::Uint8)pow(optimalisation_level, 2);

	this->initialize();
}

void FractalRenderer::generate()
{
	if (this->isSynchronized())
	{
		for (size_t i = 0; i < m_threads_Ammount; i++)
		{
			m_threads[i]->launch();
		}
	}
}

void FractalRenderer::synchronize()
{
	for (size_t i = 0; i < m_threads_Ammount; i++)
	{
		m_threads[i]->wait();
	}
}

void FractalRenderer::update()
{
	if (this->isSynchronized())
	{
		m_renderTexture.clear(sf::Color::Transparent);
		m_renderTexture.draw(m_sprite);
		m_renderTexture.display();
	}

}

// Setters - getters

void FractalRenderer::setPrecision(sf::Uint16 precision)
{
	m_precision = precision;
}

void FractalRenderer::precise(sf::Uint16 precision)
{
	m_precision += precision;
}

sf::Uint16 FractalRenderer::getPrecision()
{
	return m_precision;
}

bool FractalRenderer::isSynchronized()
{
	m_mutex.lock();
	for (int i = 0; i < m_threads_Ammount; i++)
	{
		if (m_threadAtb[i].isActive())
		{
			m_mutex.unlock();
			return false;
		}
	}
	m_mutex.unlock();
	return true;
}

bool FractalRenderer::belongsToSet(sf::Vector2md point)
{

	complex z = { 0 , 0 },
			c = {
				m_scale * (m_resolution.x / 2 + point.x / (m_size.x / m_resolution.x) - m_centerPoint.x)  - m_relativeCenter.x,
				m_scale * (m_resolution.y / 2 + point.y / (m_size.y / m_resolution.y) - m_centerPoint.y) - m_relativeCenter.y
	};

	size_t iteration = 0;
	mdType tempRe;

	while (z.Im * z.Im + z.Re * z.Re < 4.0 && ++iteration < m_precision)
	{
		tempRe = (z.Re * z.Re - z.Im * z.Im) + c.Re;
		z.Im = (2.0 * z.Re * z.Im) + c.Im;
		z.Re = tempRe;
	}

	return iteration == m_precision;
}

sf::Vector2i FractalRenderer::getGlobalResolution()
{
	return m_resolution;
}

void FractalRenderer::animateColor()
{
	m_renderSprite.setColor(
		sf::Color(
		(sf::Uint8)(200 + 55 * sin(0.5 + m_colorClock.getElapsedTime().asSeconds() / 6.0)),
			(sf::Uint8)(200 + 55 * cos(1.5 + m_colorClock.getElapsedTime().asSeconds() / 3.0)),
			(sf::Uint8)(200 + 55 * sin(1.5 + m_colorClock.getElapsedTime().asSeconds() / 6.0))
		)
	);
}

void FractalRenderer::setScale(mdType scale)
{
	m_scale = scale;
}

void FractalRenderer::scale(mdType scale)
{
	m_scale *= scale;
}

mdType FractalRenderer::getScale()
{
	return m_scale;
}

void FractalRenderer::setCenter(sf::Vector2md center)
{
	m_relativeCenter = center;
}

void FractalRenderer::setPosition(sf::Vector2md position, bool scale = true)
{
	if (scale)
	{
		m_displacement = position * m_scale;
	}
	else
	{
		m_displacement = position;
	}
}

void FractalRenderer::setViewPosition(sf::Vector2f position)
{
	m_renderSprite.setPosition(position);
}

void FractalRenderer::moveGlobal(sf::Vector2md vector, bool scale = true)
{

	// move the sprite

	m_renderDisplacement = sf::Vector2f(0.0, 0.0);

	m_renderTexture.move((float)vector.x, (float)vector.y);

	m_renderDisplacement += sf::Vector2f((float)vector.x, (float)vector.y);

	// move the fractal

	if (scale)
	{
		vector.x *=  m_scale;
		vector.y *=  m_scale;
	}

	vector.x *= static_cast<mdType>(m_resolution.x) / static_cast<mdType>(m_size.x);
	vector.y *= static_cast<mdType>(m_resolution.y) / static_cast<mdType>(m_size.y);

	m_displacement += sf::Vector2md(vector.x, vector.y);
}

void FractalRenderer::moveView(sf::Vector2md vector)
{
	m_renderDisplacement = sf::Vector2f(0.0, 0.0);

	m_renderTexture.move((float)vector.x, (float)vector.y);

	m_renderDisplacement += sf::Vector2f((float)vector.x, (float)vector.y);
}

void FractalRenderer::moveFractal(sf::Vector2md vector, bool scale = true)
{
	if (scale)
	{
		vector.x *= m_scale;
		vector.y *= m_scale;
	}

	vector.x *= static_cast<mdType>(m_resolution.x) / static_cast<mdType>(m_size.x);
	vector.y *= static_cast<mdType>(m_resolution.y) / static_cast<mdType>(m_size.y);

	m_displacement += sf::Vector2md(vector.x, vector.y);
}

sf::Vector2md FractalRenderer::getPosition()
{
	return m_displacement;
}

void FractalRenderer::initialize()
{
	m_threadAtb = new mdProperties[m_threads_Ammount];

	m_threads = new sf::Thread * [m_threads_Ammount];
	for (size_t i = 0; i < m_threads_Ammount; i++)
	{
		m_threads[i] = new sf::Thread(std::bind(&mdAlgorithm, this, i));
	}

	sf::Uint8 temp = 0;
	sf::FloatRect temprect;
	float tempSize = (float)sqrt(m_threads_Ammount);

	for (size_t j = 0; j < tempSize; j++)
	{
		for (size_t i = 0; i < tempSize; i++)
		{
			temprect.left = static_cast<float>(i)* temprect.width;
			temprect.top = static_cast<float>(j)* temprect.height;

			if (i + 1 >= tempSize)
			{
				temprect.width = (float)m_resolution.x - temprect.left;
			}
			else temprect.width = (float)m_resolution.x / static_cast<float>(tempSize);

			if (j + 1 >= tempSize)
			{
				temprect.height = (float)m_resolution.y - temprect.top;
			}
			else temprect.height = (float)m_resolution.y / (float)tempSize;

			
			unsigned int t = static_cast<unsigned int>(temp);
			m_threadAtb[t].object = this;
			m_threadAtb[t].init(
				temp,
				sf::IntRect((int)temprect.left, (int)temprect.top, (int)temprect.width, (int)temprect.height)
			);

			temp++;
		}
	}
}

void FractalRenderer::clear()
{
	this->synchronize();
	delete[] m_threadAtb;

	for (size_t i = 0; i < m_threads_Ammount; i++)
	{
		delete m_threads[i];
	}
	delete[] m_threads;
}

void FractalRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_renderSprite, states);
}
