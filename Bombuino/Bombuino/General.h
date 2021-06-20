// General.h

#ifndef _GENERAL_h
#define _GENERAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class General
{
	public:
		static const int FPS;

		static int PlayerStartPositionX;
		static int PlayerStartPositionY;
		static int PlayerWidth;
		static int PlayerHeight;

		static int LineHeightScore;

		const static int BombeTimer;

	private:
		General() {}
};

#endif

