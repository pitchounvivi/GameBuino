// Entity.h

#ifndef _ENTITY_h
#define _ENTITY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Entity {
	protected:
	int _x;
	int _y;
	int _width;
	int _height;

	public:
		virtual void update();

	const int& getX() const;

	void setX(const int& x);

	const int& getY() const;

	void setY(const int& y);

	const int& getWidth() const;

	void setWidth(const int& width);

	const int& getHeight();

	void setHeight(const int& height);
};

#endif

