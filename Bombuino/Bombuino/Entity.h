// Entity.h

#ifndef _ENTITY_h
#define _ENTITY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum TypeEntity {
	briques =0,
	bombes=1,
	players=2,
	briquesDestructible=3,
	Ia=4
};

class Entity {
	protected:
	int _x;
	int _y;
	int _width;
	int _height;
	TypeEntity _typeEntity;

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

		const TypeEntity& getTypeEntity();
};

#endif

