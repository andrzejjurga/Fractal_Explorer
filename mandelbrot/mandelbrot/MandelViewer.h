#pragma once
#include <SFML/Graphics.hpp>
#include <complex>


// typedefs ##########################################################

typedef long double mdType;

namespace sf
{
	typedef Vector2<mdType> Vector2md;
}

// Classes and structures. ###########################################


struct mdProperties;
class MandelViewer;
void mdAlgorithm(MandelViewer* object, sf::Uint8 thread_ID);


// Declarations ######################################################


struct mdProperties // Thread properties.
{
	sf::Uint8 thread_ID;
	sf::IntRect rectangle; // Image boundaries.
	sf::Uint8* pixels;
	std::complex<mdType> z[2]; // complex numbers

	void init(sf::Uint8 id, sf::IntRect r);
	void setPixel(sf::Uint16 x, sf::Uint16 y, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A);
};

class MandelViewer: public sf::Drawable
{
public:

	MandelViewer();
	MandelViewer(sf::Vector2i size, sf::Uint8 threads_Ammount);

	~MandelViewer();

	void create (sf::Vector2i size, sf::Uint8 threads_Ammount);

	void generate();
	void synchronize();

	void setPrecision(sf::Uint16 precision);
	void precise(sf::Uint16 precision);
	void setScale(mdType scale);
	void scale(mdType scale);
	void imageScale(float x, float y);
	void setImageScale(float x, float y);
	void setPosition(sf::Vector2md position);
	void move(sf::Vector2md vector, bool scale);

	friend void mdAlgorithm(MandelViewer *object, sf::Uint8 thread_ID);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	//General attributes
	sf::Uint16    m_precision;
	sf::Vector2i  m_size;
	sf::Vector2md m_centerPoint;
	sf::Vector2md m_displacement;
	mdType        m_scale;

	//Thread attributes.
	sf::Uint8     m_threads_Ammount;
	mdProperties* m_threadAtb;			 //Sets of properties for every thread.
	sf::Thread**  m_threads;			 //Double pointer allows to create threads at any time.
	sf::Mutex     m_mutex;				 //Mutex common for all threads.

	sf::Texture   m_texture;
	sf::Sprite    m_sprite;
};

