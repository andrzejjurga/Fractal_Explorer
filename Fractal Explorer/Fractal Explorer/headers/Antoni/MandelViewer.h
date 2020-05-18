///////////////////////////////////////////////////////////////////////////////////////////////////////////

// FractalRenderer::create( trzy parametry )
//		Parametr 1: rozmiar obrazka z fraktalem.
//		Parametr 2: rozdzielczoœæ fraktala (Musi byæ mniejsza lub równa rozmiarowi z parametru 1)
//		Parametr 3: optymalizacja (im wy¿sza wartoœæ, tym wiêcej w¹tków jest przeznaczona na generowanie)

// FractalRenderer::move( dwa parametry)
//		Parametr 1: Wartoœæ o jak¹ przesuniemy siê na fraktalu
//		Parametr 2:
//			Je¿eli prawda, skaluje wartoœæ, ¿eby odpowiada³a przybli¿eniu.
//			Je¿eli fa³sz, okreœla rzeczywiste przesuniêcie na uk³adzie wspó³rzêdnych (Fraktal znajduje siê w kole o promieniu 2 i œrodku (0,0) )
// fractal.move({ 1.5,0 }, false);

#pragma once
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ExpRenderTexture.h>

// Classes and structures. ###########################################


class mdProperties;
struct complex;
class FractalRenderer;
void mdAlgorithm(FractalRenderer* object, sf::Uint8 thread_ID);

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
	FractalRenderer* object;

};

class FractalRenderer: public sf::Drawable
{
public:

	friend void mdAlgorithm(FractalRenderer* object, sf::Uint8 thread_ID);
	friend mdProperties;

public:

	FractalRenderer();

	~FractalRenderer();

	void create (sf::Vector2i resolution, sf::Vector2i size, sf::Uint8 threads_Ammount);
	void generate();
	void synchronize();
	void update();

	void       setPrecision(sf::Uint16 precision);
	void       precise(sf::Uint16 precision);
	sf::Uint16 getPrecision();

	void   setScale(mdType scale);
	void   scale(mdType scale);
	mdType getScale();

	void          setCenter(sf::Vector2md center);
	void          setPosition(sf::Vector2md position, bool scale);
	void          setViewPosition(sf::Vector2f position);
	sf::Vector2md getPosition();

	void moveGlobal(sf::Vector2md vector, bool scale);
	void moveView(sf::Vector2md vector);
	void moveFractal(sf::Vector2md vector, bool scale);

	bool         isSynchronized();
	bool         belongsToSet(sf::Vector2md point);
	sf::Vector2i getGlobalResolution();

	void animateColor();

private:

	void initialize();
	void clear();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	//Additional
	sf::Clock m_colorClock; // Changes the color of the fractal over time.

	//General attributes
	sf::Vector2i  m_resolution;
	sf::Vector2i  m_size;
	sf::Uint16    m_precision;
	sf::Vector2md m_centerPoint;
	sf::Vector2md m_relativeCenter;
	sf::Vector2md m_displacement;
	mdType        m_scale;

	//Thread attributes.
	//WARNING: THE PROPERTIES BELOW ARE VERY VULNERABLE TO ANY CHANGE.
	//You don't want to touch them in any case.

	sf::Uint8     m_threads_Ammount;
	mdProperties* m_threadAtb;			//Sets of properties for every thread.
	sf::Thread**  m_threads;
	sf::Mutex     m_mutex;				//Mutex common for all threads.

	//Graphics.
	sf::Vector2f		  m_renderDisplacement;
	ExpandedRenderTexture m_renderTexture;
	sf::Sprite			  m_renderSprite;

	sf::Texture			  m_texture;
	sf::Sprite			  m_sprite;
};

