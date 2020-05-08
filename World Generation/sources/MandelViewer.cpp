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

void mdAlgorithm(MandelViewer* object, sf::Uint8 thread_ID)
{
	object->m_mutex.lock();

		object->m_threadAtb[thread_ID].isWorking = true;

		sf::RenderWindow *window   = object->m_window;
		mdType        scale        = object->m_scale;
		mdType        precision    = object->m_precision;
		sf::Vector2md center       = object->m_centerPoint;
		sf::Vector2md displacement = object->m_displacement;
		sf::IntRect   rectangle    = object->m_threadAtb[thread_ID].rectangle;
		mdProperties* ptr          =&object->m_threadAtb[thread_ID];

	object->m_mutex.unlock();

	complex z, c;
	size_t iteration;
	mdType tempRe;

	for (mdType y = 0; y < rectangle.height; y++)
	{
		for(mdType x = 0; x < rectangle.width; x++)
		{
			iteration = 0;
			z = { 0 , 0 };
			c = {
				scale * (rectangle.left + x - center.x) - displacement.x,
				scale * (rectangle.top  + y - center.y) - displacement.y
			};

			while (z.Im * z.Im + z.Re * z.Re < 4.0 && ++iteration < precision)
			{
				tempRe = (z.Re * z.Re - z.Im * z.Im) + c.Re;
				z.Im   = (2.0 * z.Re * z.Im) + c.Im;
				z.Re   = tempRe ;
			}

			if (iteration == precision)
				ptr->image.setPixel((unsigned int)x, (unsigned int)y,sf::Color::Black);
			else 
				ptr->image.setPixel(
					(unsigned int)x,
					(unsigned int)y,
					sf::Color(
						(sf::Uint8)(100 + 100 * sin(-0.5 + iteration / 51.0)),
						(sf::Uint8)(100 + 100 * sin( 1.5 + iteration / 54.0)),
						(sf::Uint8)(100 + 100 * sin( 1.5 + iteration / 56.0))
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


MandelViewer::MandelViewer()
	:m_window(nullptr),
	m_scale(0.007),
	m_threads_Ammount(0),
	m_threadAtb(nullptr),
	m_threads(nullptr)
{
	m_texture.setSmooth(true);
	m_precision = 100;
	m_scale = 0.1;
}

MandelViewer::~MandelViewer()
{
	this->clear();
}

void MandelViewer::create(sf::Vector2i resolution, sf::Vector2i size, sf::Uint8 optimalisation_level = 1)
{
	if (m_threads_Ammount > 0)
	{
		this->clear();
		m_scale = m_scale * static_cast<mdType>(m_size.x) / static_cast<mdType>(size.x);
	}
	else
	{
		m_scale = 0.007; //Default scale.
		m_texture.setSmooth(true);
		m_precision = 100;
	}

	m_size = size;
	m_resolution = resolution;
	m_centerPoint = sf::Vector2md(m_size.x / 2.0, m_size.y / 2.0);
	m_renderSprite.setTextureRect(sf::IntRect(0, 0, resolution.x, resolution.y));

	m_renderTexture.create(resolution.x, resolution.y);
	m_renderTexture.draw(m_sprite);
	m_renderTexture.display();
	m_renderSprite.setTexture(m_renderTexture.getTexture());

	m_texture.create(m_size.x, m_size.y);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
	m_sprite.setScale((float)(resolution.x / m_size.x), (float)(resolution.y / m_size.y));

	// Thread stuff

	if (optimalisation_level < 1 || optimalisation_level > 7) optimalisation_level = 1;
	m_threads_Ammount = (sf::Uint8)pow(optimalisation_level, 2);

	this->initialize();
}

void MandelViewer::generate()
{
	for (size_t i = 0; i < m_threads_Ammount; i++)
	{
		m_threads[i]->launch();
	}
}

void MandelViewer::generateInSector(sf::Uint8 sector)
{
	if (sector < m_threads_Ammount && sector >= 0)
	{
		m_threads[sector]->launch();
	}
}

void MandelViewer::synchronize()
{
	for (size_t i = 0; i < m_threads_Ammount; i++)
	{
		m_threads[i]->wait();
	}
}

void MandelViewer::update()
{
	m_mutex.lock();
	if (this->isSynchronized())
	{
		m_renderTexture.draw(m_sprite);
		m_renderTexture.display();
	}
	m_mutex.unlock();
}

// Setters - getters

void MandelViewer::setPrecision(sf::Uint16 precision)
{
	m_precision = precision;
}

void MandelViewer::precise(sf::Uint16 precision)
{
	m_precision += precision;
}

sf::Uint16 MandelViewer::getPrecision()
{
	return m_precision;
}

bool MandelViewer::isSynchronized()
{
	for (int i = 0; i < m_threads_Ammount; i++)
	{
		if (m_threadAtb[i].isActive()) return false;
	}
	return true;
}

sf::Vector2i MandelViewer::getGlobalResolution()
{
	return m_size;
}

void MandelViewer::setScale(mdType scale)
{
	m_scale = scale;
}

void MandelViewer::scale(mdType scale)
{
	m_scale *= scale;
}

mdType MandelViewer::getScale()
{
	return m_scale;
}

void MandelViewer::setWindow(sf::RenderWindow& window)
{
	m_window = &window;
}

void MandelViewer::setPosition(sf::Vector2md position)
{
	m_displacement = position;
}

void MandelViewer::move(sf::Vector2md vector, bool scale = false)
{
	m_renderDisplacement = sf::Vector2f(0.0, 0.0);

	m_renderTexture.move((float)vector.x, (float)vector.y);

	m_renderDisplacement += sf::Vector2f((float)vector.x, (float)vector.y);

	if (scale)
	{
		vector.x *=  m_scale;
		vector.y *=  m_scale;
	}

	vector.x = vector.x * static_cast<mdType>(m_size.x) / static_cast<mdType>(m_resolution.x);
	vector.y = vector.y * static_cast<mdType>(m_size.y) / static_cast<mdType>(m_resolution.y);

	m_displacement += sf::Vector2md(vector.x, vector.y);
}

void MandelViewer::initialize()
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
				temprect.width = (float)m_size.x - temprect.left;
			}
			else temprect.width = (float)m_size.x / static_cast<float>(tempSize);

			if (j + 1 >= tempSize)
			{
				temprect.height = (float)m_size.y - temprect.top;
			}
			else temprect.height = (float)m_size.y / (float)tempSize;

			
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

void MandelViewer::clear()
{
	this->synchronize();
	delete[] m_threadAtb;

	for (size_t i = 0; i < m_threads_Ammount; i++)
	{
		delete m_threads[i];
	}
	delete[] m_threads;
}

void MandelViewer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_renderSprite, states);
}
