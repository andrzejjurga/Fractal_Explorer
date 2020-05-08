#pragma once
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ExpRenderTexture.h>

// Classes and structures. ###########################################


class mdProperties;
struct complex;
class MandelViewer;
void mdAlgorithm(MandelViewer* object, sf::Uint8 thread_ID);

// typedefs ##########################################################

typedef long double mdType;

namespace sf
{
	typedef Vector2<mdType> Vector2md;
}

// Declarations ######################################################

struct complex
{
	mdType Re;
	mdType Im;
};

class mdProperties // Thread properties.
{
public:

	mdProperties();
	void init(sf::Uint8 id, sf::IntRect r);
	bool isActive();

public:

	bool isWorking;
	sf::Uint8 thread_ID;
	sf::IntRect rectangle; // Image boundaries.
	sf::Image image;
	MandelViewer* object;

};

class MandelViewer: public sf::Drawable
{
public:

	MandelViewer();

	~MandelViewer();

	void create (sf::Vector2i resolution, sf::Vector2i size, sf::Uint8 threads_Ammount);

	void generate();
	void generateInSector(sf::Uint8 sector);
	void synchronize();
	void update();

	void setPrecision(sf::Uint16 precision);
	void precise(sf::Uint16 precision);
	sf::Uint16 getPrecision();

	void setScale(mdType scale);
	void scale(mdType scale);
	mdType getScale();

	void setWindow(sf::RenderWindow &m_window);

	void setPosition(sf::Vector2md position);
	void move(sf::Vector2md vector, bool scale);

	bool isSynchronized();
	sf::Vector2i getGlobalResolution();

	friend void mdAlgorithm(MandelViewer *object, sf::Uint8 thread_ID);
	friend mdProperties;

private:

	void initialize();
	void clear();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	//Additional
	sf::RenderWindow *m_window;

	//General attributes
	sf::Vector2i  m_resolution;
	sf::Vector2i  m_size;
	sf::Uint16    m_precision;
	sf::Vector2md m_centerPoint;
	sf::Vector2md m_displacement;
	sf::Clock     m_clock;
	mdType        m_scale;

	//Thread attributes.
	sf::Uint8     m_threads_Ammount;
	mdProperties* m_threadAtb;			//Sets of properties for every thread.
	sf::Thread** m_threads;
	sf::Mutex     m_mutex;				//Mutex common for all threads.

	//Graphics.
	sf::Vector2f		  m_renderDisplacement;
	ExpandedRenderTexture m_renderTexture;
	sf::Sprite			  m_renderSprite;

	sf::Texture			  m_texture;
	sf::Sprite			  m_sprite;
};

