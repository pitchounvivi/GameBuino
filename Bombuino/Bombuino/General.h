// General.h

#ifndef _GENERAL_h
#define _GENERAL_h
#include "Entity.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class General
{
	public:
		static const int FPS;

		static int PlayersStartPositionX;
		static int PlayersStartPositionY;

		static int LineHeightScore;

		const static int BombeTimer;
		const static int maxEntite = 300;
		static Entity* EntityArray[maxEntite];

	private:
		General() {}
};

#endif

